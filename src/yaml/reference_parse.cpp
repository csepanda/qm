#include <regex>

#include <qm/parsers.hpp>


namespace YAML {

Node convert<qm::parsers::yaml::YamlReference>::encode(const qm::parsers::yaml::YamlReference &) {
    throw std::logic_error("not implemented");
}

bool
convert<qm::parsers::yaml::YamlReference>::decode(const Node &node, qm::parsers::yaml::YamlReference &yamlReference) {
    const auto referenceYamlString = node.as<std::string>();

    std::smatch m;

    if (std::regex_match(referenceYamlString, m, std::regex{R"(^Ref!\s+(\w+)$)"})) {
        yamlReference.Id = m[1].str();
        yamlReference.Resolved = false;
        return true;
    } else {
        throw qm::parsers::ParseException("Expected reference, but reference format is not matched", referenceYamlString);
    }
}
}
