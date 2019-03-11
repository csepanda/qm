#include <qm/yaml/dto/File.hpp>

namespace qm::yaml::dto {

std::unique_ptr<qm::models::File> File::GetModel() const {
    switch (Type) {
        case models::FileType::Regular:
            return getRegularFile();
        default:
            throw std::logic_error("Handler for this FileType is not implemented");
    }
}

std::unique_ptr<qm::models::RegularFile> File::getRegularFile() const {
    switch (RegularSourceType) {
        case RegularFileSourceType::Text:
            return std::make_unique<qm::models::TextFile>(Path, TextContent);
        default:
            throw std::logic_error("Handler for this regular file's source type is not implemented");
    }
}
}
