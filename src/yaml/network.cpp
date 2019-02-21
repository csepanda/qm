#include <vector>
#include <unordered_map>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <qm/parsers.hpp>

namespace qm::parsers::yaml {
const qm::models::Network NetworkYamlDTO::GetNetwork() const {
    std::vector<std::shared_ptr<qm::models::Node>> nodes{};
    std::vector<std::shared_ptr<qm::models::Connection>> connections{};

    for (const auto &[_, dto] : NodesDTO) {
        nodes.push_back(dto.Node);
    }
    for (const auto &[_, dto] : ConnectionsDTO) {
        connections.push_back(dto.GetConnection());
    }

    return qm::models::Network(nodes, connections);
}
}

namespace YAML {

Node convert<qm::parsers::yaml::NetworkYamlDTO>::encode(const qm::parsers::yaml::NetworkYamlDTO &networkYamlDTO) {
    throw std::logic_error("Not implemented");
}

static void SetIdIfNotSet(qm::parsers::yaml::IdentifiableDTO &obj, boost::uuids::random_generator generator) {
    if (obj.GetId().empty()) {
        const auto uuid = generator();
        const auto id = boost::uuids::to_string(uuid);

        obj.SetId(id);
    }
}

template<typename T>
void parseObjectsSequence(const Node &node, std::unordered_map<std::string, T> &resultMap,
                          boost::uuids::random_generator &generator) {
    if (!node.IsDefined()) {
        return;
    }

    if (!node.IsSequence()) {
        throw qm::parsers::ParseException("Expected array", "Network yaml parsing");
    }

    for (const auto &nodeYaml : node) {
        auto parsedObject = nodeYaml.as<T>();

        SetIdIfNotSet(parsedObject, generator);
        resultMap[parsedObject.GetId()] = parsedObject;
    }

}

bool convert<qm::parsers::yaml::NetworkYamlDTO>::decode(const Node &node,
                                                        qm::parsers::yaml::NetworkYamlDTO &networkYamlDTO) {
    boost::uuids::random_generator generateUUID;
    const auto nodesYaml = node["nodes"];
    const auto connectionsYaml = node["connections"];

    parseObjectsSequence(nodesYaml, networkYamlDTO.NodesDTO, generateUUID);
    parseObjectsSequence(connectionsYaml, networkYamlDTO.ConnectionsDTO, generateUUID);

    networkYamlDTO.ResolveContext();

    return true;
}
}

