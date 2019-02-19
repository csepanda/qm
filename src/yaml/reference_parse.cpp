#include <qm/parsers.hpp>

namespace YAML {

Node convert<qm::parsers::yaml::YamlReference>::encode(const qm::parsers::yaml::YamlReference &) {
    throw std::logic_error("not implemented");
}

bool
convert<qm::parsers::yaml::YamlReference>::decode(const Node &node, qm::parsers::yaml::YamlReference &yamlReference) {
    const auto id = node.as<std::string>();
    const auto &type = node.Tag();

    if (type == "!Ref") {
        yamlReference.Id = id;
        yamlReference.Resolved = false;
        return true;
    } else {
        throw qm::parsers::ParseException("Expected reference with !Ref tag, got: '" + type + "'", "");
    }
}
}
