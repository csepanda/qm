#include <qm/parsers.hpp>

namespace YAML {

Node convert<qm::yaml::dto::YamlReference>::encode(const qm::yaml::dto::YamlReference &) {
    throw std::logic_error("Not implemented");
}

bool
convert<qm::yaml::dto::YamlReference>::decode(const Node &node, qm::yaml::dto::YamlReference &yamlReference) {
    const auto id = node.as<std::string>();
    const auto &type = node.Tag();

    if (type == "!Ref") {
        yamlReference.Id = id;
        yamlReference.Resolved = false;
        return true;
    } else {
        throw qm::ParseException("Expected reference with !Ref tag, got: '" + type + "'", "");
    }
}
}
