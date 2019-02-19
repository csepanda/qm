#ifndef QM_YAML_DTO_H
#define QM_YAML_DTO_H

#include <vector>
#include <unordered_map>

#include <qm/model.hpp>

namespace qm::parsers::yaml {
struct YamlReference {
    std::string Id;
    bool Resolved;
};

struct IPAddressYamlDTO {
    qm::models::IPVersion ProtocolVersion{};
    qm::models::IPv4Address IPv4;
    //qm::models::IPv6Address IPv6;
};

struct IPNetworkYamlDTO {
    qm::models::IPVersion ProtocolVersion{};
    qm::models::IPv4Network IPv4{};
    // qm::models::IPv6Address IPv6;
};

struct IpConfigYamlDTO {
    YamlReference ConnectionRef;
    qm::models::IpConfig IpConfig;
};

struct ConnectionYamlDTO {
    std::vector<YamlReference> TargetsRefs;
    qm::models::ConnectionType type;
    std::shared_ptr<qm::models::PointToPointConnection> p2p;

    std::shared_ptr<qm::models::Connection> GetConnection() {
        switch (type) {
            case models::ConnectionType::P2P:
                return p2p;
        }
    }
};

struct NodeYamlDTO {
    std::shared_ptr<qm::models::Node> Node;
    std::vector<IpConfigYamlDTO> IpConfigs{};
};


struct NetworkYamlDTO {
    std::unordered_map<std::string, NodeYamlDTO> NodesDTO{};
    std::unordered_map<std::string, ConnectionYamlDTO> ConnectionsDTO{};

    void ResolveContext();
};
}
#endif //QM_YAML_DTO_H
