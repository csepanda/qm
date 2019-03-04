#ifndef QM_PARSERS_IPUTILS_HPP
#define QM_PARSERS_IPUTILS_HPP

#include <qm/model.hpp>

namespace qm::parsers {
class IpUtils {
public:
    static qm::models::IPVersion determineIPVersion(const std::string &address);

    static std::array<uint8_t, 4> parseIPv4(const std::string &address);

    static std::array<uint8_t, 16> parseIPv6(const std::string &address);

    static uint32_t parseCIDR(const std::string &cidr);
};
}

#endif //QM_PARSERS_IPUTILS_HPP
