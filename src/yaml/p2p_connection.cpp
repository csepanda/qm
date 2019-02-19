#include <qm/parsers.hpp>
#include <unordered_map>

namespace YAML {

static const qm::models::ConnectionType DEFAULT_TYPE = qm::models::ConnectionType::P2P;
static const std::unordered_map<std::string, qm::models::ConnectionType> typeMapper{
  {"p2p",          qm::models::ConnectionType::P2P},
  {"P2P",          qm::models::ConnectionType::P2P},
  {"PointToPoint", qm::models::ConnectionType::P2P}
};

Node convert<qm::parsers::yaml::ConnectionYamlDTO>::encode(const qm::parsers::yaml::ConnectionYamlDTO &connectionDTO) {
    Node node;

    switch (connectionDTO.type) {
        case qm::models::ConnectionType::P2P:
        default:
            throw std::logic_error("Not implemented");
    }
}

bool convert<qm::parsers::yaml::ConnectionYamlDTO>::decode(const Node &node,
                                                           qm::parsers::yaml::ConnectionYamlDTO &connectionDTO) {
    const auto typeNode = node["type"];

    if (typeNode.IsDefined()) {
        const auto type = typeNode.as<std::string>();

        try {
            connectionDTO.type = typeMapper.at(type);
        } catch (std::out_of_range&) {
            throw qm::parsers::ParseException("Unknown connection type: '" + type + "'", "Parse Connection from yaml");
        }
    } else {
        connectionDTO.type = DEFAULT_TYPE;
    }

    switch (connectionDTO.type) {
        case qm::models::ConnectionType::P2P: {
            connectionDTO.p2p = std::make_shared<qm::models::PointToPointConnection>();

            const auto id = node["id"];
            const auto mtuNode = node["mtu"];
            const auto dataRateNode = node["dataRate"];
            const auto delayNode = node["delay"];

            if (id.IsDefined()) {
                connectionDTO.p2p->SetId(id.as<std::string>());
            }

            if (mtuNode.IsDefined()) {
                connectionDTO.p2p->setMtu(mtuNode.as<uint16_t>());
            }

            if (dataRateNode.IsDefined()) {
                connectionDTO.p2p->setDataRate(dataRateNode.as<std::string>());
            }

            if (delayNode.IsDefined()) {
                connectionDTO.p2p->setDelay(delayNode.as<std::string>());
            }

            const auto targets = node["targets"];

            if (targets.IsDefined()) {
                if (!targets.IsSequence()) {
                    throw qm::parsers::ParseException("Connection's targets should be a sequence", "Connection");
                }

                for (const auto& target : targets) {
                    const auto ref = target.as<qm::parsers::yaml::YamlReference>();

                    connectionDTO.TargetsRefs.push_back(ref);
                }
            }
            break;
        }
        default:
            throw std::logic_error("Not implemented");
    }

    return true;
}
}

