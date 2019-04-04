#ifndef QM_YAML_DTO_FILE_HPP
#define QM_YAML_DTO_FILE_HPP

#include <qm/models/File.hpp>
#include <qm/models/ConfigurationFiles/BgpConfig.hpp>
#include "Index.hpp"

namespace qm::yaml::dto {
enum class RegularFileType {
    Text,
    ZebraConfig,
    BgpConfig
};

struct BgpNeighbor {
    std::string IpAddress;
    uint16_t As;
    bool NextHopSelf;
    bool Activated;
};

struct BgpConfigDTO {
    uint16_t As;
    std::vector<BgpNeighbor> Neighbors;
};

struct File : public BaseYamlDTO<std::unique_ptr<qm::models::File>> {
    qm::models::FileType Type {};
    std::string Path {};

    RegularFileType RegularSourceType {};
    std::string TextContent {};

    BgpConfigDTO bgp;

    std::unique_ptr<qm::models::File> GetModel() const override;

private:
    std::unique_ptr<qm::models::RegularFile> getRegularFile() const;
};
}

#endif //QM_YAML_DTO_FILE_HPP
