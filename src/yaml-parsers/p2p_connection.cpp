#include <qm/parsers.hpp>
#include <unordered_map>

namespace YAML {

static const qm::models::ConnectionType DEFAULT_TYPE = qm::models::ConnectionType::P2P;
static const std::unordered_map<std::string, qm::models::ConnectionType> typeMapper {
  {"p2p", qm::models::ConnectionType::P2P},
  {"PointToPoint", qm::models::ConnectionType::P2P}
};

Node convert<qm::parsers::yaml::ConnectionYamlDTO>::encode(const qm::parsers::yaml::ConnectionYamlDTO &connectionDTO) {
    Node node;

    switch (connectionDTO.type) {
        case qm::models::ConnectionType::P2P:
        default:
            throw std::logic_error("Not implemented");
    }

    return node;
}

bool convert<qm::parsers::yaml::ConnectionYamlDTO>::decode(const Node &node,
                                                           qm::parsers::yaml::ConnectionYamlDTO &connectionDTO) {
    const auto typeNode = node["type"];

    if (typeNode.IsDefined()) {
        connectionDTO.type = typeMapper.at(node["type"].as<std::string>());
    } else {
        connectionDTO.type = DEFAULT_TYPE;
    }

    switch (connectionDTO.type) {
        case qm::models::ConnectionType::P2P: {
            connectionDTO.p2p = std::make_shared<qm::models::PointToPointConnection>();

            const auto mtuNode = node["mtu"];
            const auto dataRateNode = node["dataRate"];
            const auto delayNode = node["delay"];

            if (mtuNode.IsDefined()) {
                connectionDTO.p2p->setMtu(mtuNode.as<uint16_t>());
            }

            if (dataRateNode.IsDefined()) {
                connectionDTO.p2p->setDataRate(dataRateNode.as<std::string>());
            }

            if (delayNode.IsDefined()) {
                connectionDTO.p2p->setDelay(delayNode.as<std::string>());
            }
            break;
        }
        default:
            throw std::logic_error("Not implemented");
    }

    return true;
}
}

