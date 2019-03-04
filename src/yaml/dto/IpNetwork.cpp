#include <qm/yaml/dto/IpNetwork.hpp>

namespace qm::yaml::dto {

std::shared_ptr<models::IPNetwork> IPNetwork::GetModel() const {
    switch (ProtocolVersion) {
        case models::IPv4:
            return IPv4;
        case models::IPv6:
            throw std::logic_error("Not implemented");
        default:
            throw std::logic_error("Unsupported protocol version");
    }
}
}
