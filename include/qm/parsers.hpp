#include <cstdint>
#include <array>

namespace qm::parsers {
std::array<uint8_t, 4> parseIPv4(const std::string& address);

std::array<uint8_t, 16> parseIPv6(const std::string& address);

uint32_t parseCIDR(const std::string& cidr);

struct ParseException : public std::runtime_error {
    const std::string m_source;

    explicit ParseException(const std::string &message, std::string source) :
            std::runtime_error(message),
            m_source(std::move(source)) {
    }
};
}