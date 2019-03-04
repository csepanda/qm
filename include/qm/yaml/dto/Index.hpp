#ifndef QM_YAML_DTO_H
#define QM_YAML_DTO_H

#include <vector>
#include <unordered_map>
#include <memory>

#include <qm/exceptions.hpp>
#include <qm/models.hpp>

namespace qm::parsers::yaml {
template<typename TModel>
class BaseYamlDTO {
public:
    virtual TModel GetModel() const = 0;
};

class IdentifiableDTO {
public:
    virtual const std::string &GetId() const = 0;

    virtual void SetId(std::string id) = 0;
};

struct YamlReference {
    std::string Id;
    bool Resolved;
};

struct IpConfigYamlDTO {
    YamlReference ConnectionRef;
    std::shared_ptr<qm::models::IpConfig> IpConfig;
};

}
#endif //QM_YAML_DTO_H
