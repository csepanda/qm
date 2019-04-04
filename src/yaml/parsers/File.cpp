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

bool convert<qm::yaml::dto::RegularFileType>::decode(const Node &node, qm::yaml::dto::RegularFileType &fileType) {
    auto str = node.as<std::string>();

    if (str == "bgpConfig" || str == "bgp") {
        fileType = qm::yaml::dto::RegularFileType::BgpConfig;
    } else if (str == "zebraConfig" || str == "zebra") {
        fileType = qm::yaml::dto::RegularFileType::ZebraConfig;
    } else if (str == "text" || str == "txt") {
        fileType = qm::yaml::dto::RegularFileType::Text;
    } else {
        throw qm::ParseException("Unknown RegularFileType: " + str, "File parsing");
    }

    return true;
}

bool convert<qm::yaml::dto::BgpNeighbor>::decode(const Node &node, qm::yaml::dto::BgpNeighbor &neighbor) {
    const auto ipAddressNode = node["address"];
    const auto asNode = node["as"];
    const auto nextHopSelfNode = node["nextHopSelf"];
    const auto activatedNode = node["activate"];

    if (!ipAddressNode.IsDefined()) {
        throw qm::ParseException("address is required for neighbor", "BgpConfig parsing");
    }

    if (!ipAddressNode.IsDefined()) {
        throw qm::ParseException("as is required for neighbor", "BgpConfig parsing");
    }

    neighbor.IpAddress = ipAddressNode.as<std::string>();
    neighbor.As = asNode.as<uint16_t >();
    neighbor.NextHopSelf = nextHopSelfNode.IsDefined() ? nextHopSelfNode.as<bool>() : true;
    neighbor.Activated = activatedNode.IsDefined() ? activatedNode.as<bool>() : true;

    return true;
}

bool decodeRegularFile(const Node &node, qm::yaml::dto::File &fileDTO) {
    const auto regularFileType = node["kind"];

    if (regularFileType.IsDefined()) {
        fileDTO.RegularSourceType = regularFileType.as<qm::yaml::dto::RegularFileType>();
    } else {
        fileDTO.RegularSourceType = qm::yaml::dto::RegularFileType::Text;
    }

    switch (fileDTO.RegularSourceType) {
        case qm::yaml::dto::RegularFileType::Text: {
            const auto textContentNode = node["text"];

            if (textContentNode.IsDefined() && textContentNode.IsScalar()) {
                fileDTO.TextContent = textContentNode.as<std::string>();
            } else {
                throw qm::ParseException("text content of file should be a string", "files parsing");
            }

            break;
        }
        case qm::yaml::dto::RegularFileType::ZebraConfig:
            break;
        case qm::yaml::dto::RegularFileType::BgpConfig: {
            const auto asNode = node["as"];
            const auto neighborsNode = node["neighbors"];

            if (!asNode.IsDefined()) {
                throw qm::ParseException("as is required field", "bgp config");
            }

            fileDTO.bgp.As = asNode.as<uint16_t>();

            if (neighborsNode.IsDefined()) {
                fileDTO.bgp.Neighbors = neighborsNode.as<std::vector<qm::yaml::dto::BgpNeighbor>>();
            }

            break;
        }
    }

    return true;
}

bool convert<qm::yaml::dto::File>::decode(const Node &node, qm::yaml::dto::File &fileDTO) {
    const auto typeNode = node["type"];
    const auto pathNode = node["path"];

    if (pathNode.IsDefined()) {
        fileDTO.Path = pathNode.as<std::string>();
    } else {
        throw qm::ParseException("path is required field of file", "files parsing");
    }

    if (typeNode.IsDefined()) {
        fileDTO.Type = typeNode.as<qm::models::FileType>();
    }

    switch (fileDTO.Type) {
        case qm::models::FileType::Regular:
            return decodeRegularFile(node, fileDTO);
        default:
            throw std::logic_error(
              "Handler for this FileType is not implemented " + std::to_string((int) fileDTO.Type));
    }
}
}
