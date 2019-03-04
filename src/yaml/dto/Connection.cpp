#include <qm/yaml/dto/Connection.hpp>

namespace qm::yaml::dto {

std::shared_ptr<qm::models::Connection> Connection::GetModel() const {
    switch (type) {
        case models::ConnectionType::P2P:
            return p2p;
    }
}

const std::string &Connection::GetId() const {
    switch (type) {
        case models::ConnectionType::P2P: {
            if (p2p == nullptr) {
                throw qm::UninitializedException("Type is P2P, but P2P is not initialized");
            }

            return p2p->GetId();
        }
    }
}

void Connection::SetId(std::string id) {
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
