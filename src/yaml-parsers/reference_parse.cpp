#include <regex>

#include <qm/parsers.hpp>


namespace qm::parsers::yaml {
YamlReference parseYamlReference(const std::string &reference) {
    std::smatch m;

    if (std::regex_match(reference, m, std::regex {R"(^Ref!\s+(\w+)$)"})) {
        YamlReference ref;

        ref.Id = m[0];
        ref.Resolved = false;

        return ref;
    } else {
        throw ParseException("Expected reference, but reference format is not matched", reference);
    }
}
}

