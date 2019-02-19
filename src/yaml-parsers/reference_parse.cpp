#include <regex>

#include <qm/parsers.hpp>
#include <qm/yaml-parsers/yaml_reference.hpp>

namespace qm::parsers::yaml {
YamlReference parseYamlReference(const std::string &reference) {
    std::smatch m;

    if (std::regex_match(reference, m, std::regex {R"(^Ref!\s+(\w+)$)"})) {
        YamlReference ref;

        ref.Id = m[1].str();
        ref.Resolved = false;

        return ref;
    } else {
        throw ParseException("Expected reference, but reference format is not matched", reference);
    }
}
}

namespace YAML {

Node convert<qm::parsers::yaml::YamlReference>::encode(const qm::parsers::yaml::YamlReference &) {
    throw std::logic_error("not implemented");
}

bool convert<qm::parsers::yaml::YamlReference>::decode(const Node &node, qm::parsers::yaml::YamlReference &yamlReference) {
    const auto referenceYamlString = node.as<std::string>();
    const auto parsed = qm::parsers::yaml::parseYamlReference(referenceYamlString);

    yamlReference.Id = parsed.Id;
    yamlReference.Resolved = parsed.Resolved;

    return true;
}

}

