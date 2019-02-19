#ifndef QM_YAML_DTO_H
#define QM_YAML_DTO_H

#include <vector>
#include <unordered_map>

#include <qm/exceptions.hpp>
#include <qm/model.hpp>

namespace qm::parsers::yaml {
class IdentifiableDTO {
public:
    virtual const std::string& GetId() const = 0;
    virtual void SetId(std::string id) = 0;
};

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

struct ConnectionYamlDTO : public IdentifiableDTO {
    std::vector<YamlReference> TargetsRefs;
    qm::models::ConnectionType type;
    std::shared_ptr<qm::models::PointToPointConnection> p2p;

    std::shared_ptr<qm::models::Connection> GetConnection() {
        switch (type) {
            case models::ConnectionType::P2P:
                return p2p;
        }
    }

    const std::string& GetId() const override {
        switch (type) {
            case models::ConnectionType::P2P: {
                if (p2p == nullptr) {
                    throw qm::UninitializedException("Type is P2P, but P2P is not initialized");
                }

                return p2p->GetId();
            }
        }
    }

    void SetId(std::string id) override {
        switch (type) {
            case models::ConnectionType::P2P: {
                if (p2p == nullptr) {
                    throw qm::UninitializedException("Type is P2P, but P2P is not initialized");
                }

                p2p->SetId(std::move(id));
            }
        }
    }
};

struct NodeYamlDTO : public IdentifiableDTO {
    std::shared_ptr<qm::models::Node> Node;
    std::vector<IpConfigYamlDTO> IpConfigs{};

    const std::string &GetId() const override {
        if (Node == nullptr) {
            throw qm::UninitializedException("Node is not initialized");
        }

        return Node->GetId();
    }

    void SetId(std::string id) override {
        if (Node == nullptr) {
            throw qm::UninitializedException("Node is not initialized");
        }

        Node->SetId(id);
    }
};

struct NetworkYamlDTO {
    std::unordered_map<std::string, NodeYamlDTO> NodesDTO{};
    std::unordered_map<std::string, ConnectionYamlDTO> ConnectionsDTO{};

    void ResolveContext();
};
}
#endif //QM_YAML_DTO_H
