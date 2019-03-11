#ifndef QM_YAML_PARSERS_FILE_HPP
#define QM_YAML_PARSERS_FILE_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/File.hpp>

namespace YAML {
template<>
struct convert<qm::models::FileType> {
    static Node encode(const qm::models::FileType &);

    static bool decode(const Node &, qm::models::FileType &);
};

template<>
struct convert<qm::yaml::dto::File> {
    static Node encode(const qm::yaml::dto::File &);

    static bool decode(const Node &, qm::yaml::dto::File &);
};
}


#endif //QM_YAML_PARSERS_FILE_HPP
