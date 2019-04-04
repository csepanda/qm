#include <qm/yaml/dto/File.hpp>
#include <qm/models/ConfigurationFiles/ZebraConfig.hpp>

namespace qm::yaml::dto {

std::unique_ptr<qm::models::File> File::GetModel() const {
    switch (Type) {
        case models::FileType::Regular:
            return getRegularFile();
        default:
            throw std::logic_error("Handler for this FileType is not implemented " + std::to_string((int) Type));
    }
}

std::unique_ptr<qm::models::RegularFile> File::getRegularFile() const {
    switch (RegularSourceType) {
        case RegularFileType::Text:
            return std::make_unique<qm::models::TextFile>(Path, TextContent);
        case RegularFileType::ZebraConfig:
            return std::make_unique<qm::models::configurations::ZebraConfig>(Path);
        case RegularFileType::BgpConfig: {
            std::vector<qm::models::configurations::BgpNeighbor> neighbors{};

            for (const auto &neighborDTO : bgp.Neighbors) {
                neighbors.emplace_back(
                  neighborDTO.IpAddress,
                  neighborDTO.As,
                  neighborDTO.NextHopSelf,
                  neighborDTO.Activated
                );
            }

            return std::make_unique<qm::models::configurations::BgpConfig>(Path, bgp.As, neighbors);
        }
        default:
            throw std::logic_error("Handler for this regular file's source type is not implemented");
    }
}
}
