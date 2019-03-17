#include <vector>
#include <unordered_map>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <qm/parsers.hpp>

namespace YAML {

Node convert<qm::yaml::dto::Network>::encode(const qm::yaml::dto::Network &networkYamlDTO) {
    throw std::logic_error("Not implemented");
}

static void SetIdIfNotSet(qm::yaml::dto::IdentifiableDTO &obj, boost::uuids::random_generator generator) {
    if (obj.GetId().empty()) {
        const auto uuid = generator();
        const auto id = boost::uuids::to_string(uuid);

        obj.SetId(id);
    }
}

template<typename T>
void parseObjectsSequence(const Node &node, std::map<std::string, T> &resultMap,
                          boost::uuids::random_generator &generator) {
    if (!node.IsDefined()) {
        return;
    }

    if (!node.IsSequence()) {
        throw qm::ParseException("Expected array", "Network yaml parsing");
    }

    for (const auto &nodeYaml : node) {
        auto parsedObject = nodeYaml.as<T>();

        SetIdIfNotSet(parsedObject, generator);
        resultMap[parsedObject.GetId()] = parsedObject;
    }

}

bool convert<qm::yaml::dto::Network>::decode(const Node &node,
                                                        qm::yaml::dto::Network &networkYamlDTO) {
    boost::uuids::random_generator generateUUID;
    const auto nodesYaml = node["nodes"];
    const auto connectionsYaml = node["connections"];

    parseObjectsSequence(nodesYaml, networkYamlDTO.NodesDTO, generateUUID);
    parseObjectsSequence(connectionsYaml, networkYamlDTO.ConnectionsDTO, generateUUID);

    networkYamlDTO.ResolveContext();

    return true;
}
}

