#ifndef QM_YAML_DTO_FILE_HPP
#define QM_YAML_DTO_FILE_HPP

#include <qm/models/File.hpp>
#include "Index.hpp"

namespace qm::yaml::dto {
enum class RegularFileSourceType {
    Text
};

struct File : public BaseYamlDTO<std::unique_ptr<qm::models::File>> {
    qm::models::FileType Type;
    std::string Path;

    RegularFileSourceType RegularSourceType;
    std::string TextContent;

    std::unique_ptr<qm::models::File> GetModel() const override;

private:
    std::unique_ptr<qm::models::RegularFile> getRegularFile() const;
};
}

#endif //QM_YAML_DTO_FILE_HPP
