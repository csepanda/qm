#include <qm/exceptions.hpp>
#include <qm/parsers.hpp>

namespace YAML {


Node convert<qm::models::FileType>::encode(const qm::models::FileType &) {
    throw std::logic_error("FileType to yaml encoder is not implemented");
}

bool convert<qm::models::FileType>::decode(const Node &node, qm::models::FileType &fileType) {
    const auto str = node.as<std::string>();

    if (str == "regular") {
        fileType = qm::models::FileType::Regular;
    } else {
        return false;
    }

    return true;
}

Node convert<qm::yaml::dto::File>::encode(const qm::yaml::dto::File &) {
    throw std::logic_error("File to yaml encoder is not implemented");
}

bool convert<qm::yaml::dto::File>::decode(const Node &node, qm::yaml::dto::File &fileDTO) {
    const auto typeNode = node["type"];
    const auto textContentNode = node["text"];

    if (typeNode.IsDefined()) {
        fileDTO.Type = typeNode.as<qm::models::FileType>();
    }

    if (textContentNode.IsDefined()) {
        if (textContentNode.IsScalar()) {
            fileDTO.TextContent = textContentNode.as<std::vector<std::string>>();
        } else if (textContentNode.IsSequence()) {
            fileDTO.TextContent = std::vector<std::string>(1, textContentNode.as<std::string>());
        } else {
            throw qm::ParseException("text content of file should be a string or sequence", "files parsing");
        }

        fileDTO.RegularSourceType = qm::yaml::dto::RegularFileSourceType::Text;
    }


    return false;
}
}
