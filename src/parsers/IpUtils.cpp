#include <regex>

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include <qm/parsers/IpUtils.hpp>
#include <qm/parsers.hpp>

namespace qm::parsers {

static const std::regex ipv4Validator{R"(^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$)"};
static const std::regex ipv6Validator{
  R"(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))"};

qm::models::IPVersion parsers::IpUtils::determineIPVersion(const std::string &address) {
    if (std::regex_match(address, ipv4Validator)) {
        return qm::models::IPv4;
    } else if (std::regex_match(address, ipv6Validator)) {
        return qm::models::IPv6;
    }

    throw ParseException("Unknown IP address protocol version", address);
}

std::array<uint8_t, 4> IpUtils::parseIPv4(const std::string &address) {
    if (!std::regex_match(address, ipv4Validator)) {
        throw ParseException("doesn't match format: x.x.x.x", address);
    }

    boost::char_separator<char> sep(".");
    boost::tokenizer<boost::char_separator<char> > tokens(address, sep);

    int index = 0;
    std::array<uint8_t, 4> out{};
    for (auto it = tokens.begin(); it != tokens.end(); ++it, ++index) {
        int val = std::stoi(*it);

        if (val > 255 || val < 0) {
            throw ParseException(
              "IPv4 component cannot contain numbers greater than 255 or less than zero",
              address);
        }

        out[index] = static_cast<unsigned char>(val);
    }

    return out;
}

std::array<uint8_t, 16> IpUtils::parseIPv6(const std::string &address) {
    if (!std::regex_match(address, ipv6Validator)) {
        throw ParseException("doesn't match ipv6 format", address);
    }

    boost::char_separator<char> sep(":");
    boost::tokenizer<boost::char_separator<char> > tokens(address, sep);

    int index = 0;
    bool has_skip = false;
    std::array<uint8_t, 16> out{};
    for (auto it = tokens.begin(); it != tokens.end(); ++it, ++index) {
        const std::string &component = *it;

        if (component.empty()) {
            if (has_skip) {
                throw ParseException(
                  "IPv6 component cannot contain more than one zero-section omission",
                  address);
            }

            out[index] = 0;
            has_skip = true;
        }

        try {
            int val = std::stoi(component, nullptr, 16);

            if (val > 0xFFFF || val < 0) {
                throw ParseException(
                  "IPv6 component cannot contain numbers greater than 0xFFFF or less than zero",
                  address);
            }

            out[index] = static_cast<unsigned char>(val);
        } catch (std::invalid_argument &e) {
            throw ParseException(
              "not a number",
              address);
        }
    }

    return out;

}

static bool is_number(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

uint32_t IpUtils::parseCIDR(const std::string &cidr) {
    if (!is_number(cidr)) {
        throw ParseException("Cannot parse CIDR mask", cidr);
    }

    return static_cast<uint32_t>(std::stoi(cidr));
}
}
