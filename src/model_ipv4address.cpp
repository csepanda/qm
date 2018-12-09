#include "model.hpp"

#include <array>
#include <boost/tokenizer.hpp>
#include <cmath>
#include <regex>
#include <string>

namespace qm::models {
static void parseIpv4Address(const std::string& address, std::array<uint8_t, 4>& out);
static IPv4Address parseIpv4Mask(const std::string& mask);

IPv4Address::IPv4Address(const std::string& address) {
	parseIpv4Address(address, m_address);
}

IPv4Address::IPv4Address(const uint32_t raw) {
    std::array<uint8_t, 4> address;

    for (int i = 0; i < 4; i++) {
        address[i] = raw >> (8 * (3 - i)) & 0xFF;
    }

    m_address = address;
}

uint64_t IPv4Address::GetRaw() {
    uint32_t raw = 0;
    for (int i = 0; i < 4; i++) {
        raw |= m_address[i] << (8 * (3 - i));
    }

    return raw;
}

std::string IPv4Address::GetAddressStr() {
    std::stringstream ss;

    ss << std::to_string(m_address[0]) << '.';
    ss << std::to_string(m_address[1]) << '.';
    ss << std::to_string(m_address[2]) << '.';
    ss << std::to_string(m_address[3]);

	return ss.str();
}


IPv4Network::IPv4Network(const std::string& address, const std::string& mask)
	: m_address{IPv4Address{address}}, m_mask{parseIpv4Mask(mask)} {
}

IPAddress* IPv4Network::GetRawAddress() {
    return &m_address;
}

IPAddress* IPv4Network::GetRawNetmask() {
    return &m_mask;
}

uint32_t IPv4Network::GetNetmaskPrefixLength() {
    uint32_t mask = m_mask.GetRaw();

    uint32_t result = 0;
    do {
        ++result;
    } while(mask <<= 1);

    return result;
}

std::string IPv4Network::GetAddressStr() {
    return m_address.GetAddressStr();
}

std::string IPv4Network::GetNetmaskStr() {
    return m_mask.GetAddressStr();
}

std::string IPv4Network::GetAddressWithMaskStr() {
    std::stringstream ss;

    ss << GetAddressStr() << "/" << GetNetmaskPrefixLength();
    return ss.str();
}

static const std::regex ipv4Validator {"^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$"};
static void parseIpv4Address(const std::string& address, std::array<uint8_t, 4>& out) {
	if (!std::regex_match(address, ipv4Validator)) {
		throw IPv4FormatException(
			"doesn't match format: x.x.x.x",
			address);
	}

	boost::char_separator<char> sep(".");
	boost::tokenizer<boost::char_separator<char> > tokens(address, sep);

	int index = 0;
	for (auto it = tokens.begin(); it != tokens.end(); ++it, ++index) {
		try {
			int val = std::stoi(*it);

			if (val > 255 || val < 0) {
				throw IPv4AddressFormatException(
					"cannot contain numbers greater than 255 or less than zero",
					address);
			}

			out[index] = val;
		} catch (std::invalid_argument e) {
			throw IPv4AddressFormatException(
				"not a number",
				address);
		}
	}
}

static const std::regex ipv4MaskValidator {"^\\d{1,3}$"};
static IPv4Address parseIpv4Mask(const std::string& mask) {
    if (std::regex_match(mask, ipv4MaskValidator)) {
        uint32_t prefix_len = std::stoi(mask);
        
        if (prefix_len > 31) {
            throw new IPv4NetmaskFormatException("invalid mask", mask);
        }

        int raw = ~((int) pow(2.0, 32 - prefix_len) - 1); 

        return IPv4Address(raw);
    } else if (std::regex_match(mask, ipv4Validator)) {
        std::array<uint8_t, 4> mask_address;

        try {
            parseIpv4Address(mask, mask_address);
        } catch (IPv4AddressFormatException& e) {
            throw IPv4NetmaskFormatException(e.what(), e.m_source);
        }

        uint32_t int_mask = 0;
        for (int i = 0; i < 4; i++) {
            int_mask |= mask_address[i] << (8 * (3 - i));
        }

        if (int_mask & (~int_mask >> 1)) {
            throw IPv4NetmaskFormatException("invalid mask", mask);
        }

        return IPv4Address(int_mask);
    } else {
        throw new IPv4NetmaskFormatException("invalid mask", mask);
    }
}
}
