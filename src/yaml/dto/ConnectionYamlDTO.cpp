#include <qm/yaml/dto/ConnectionYamlDTO.hpp>

namespace qm::yaml::dto {

std::shared_ptr<qm::models::Connection> ConnectionYamlDTO::GetModel() const {
    switch (type) {
        case models::ConnectionType::P2P:
            return p2p;
    }
}

const std::string &ConnectionYamlDTO::GetId() const {
    switch (type) {
        case models::ConnectionType::P2P: {
            if (p2p == nullptr) {
                throw qm::UninitializedException("Type is P2P, but P2P is not initialized");
            }

            return p2p->GetId();
        }
    }
}

void ConnectionYamlDTO::SetId(std::string id) {
    switch (type) {
        case models::ConnectionType::P2P: {
            if (p2p == nullptr) {
                throw qm::UninitializedException("Type is P2P, but P2P is not initialized");
            }

            p2p->SetId(std::move(id));
        }
    }
}
}
