#ifndef QM_MODELS_CFG_ZEBRACONFIG_HPP
#define QM_MODELS_CFG_ZEBRACONFIG_HPP

#include <qm/models/File.hpp>

namespace qm::models::configurations {
class ZebraConfig : public ConfigurationFile {
public:
    explicit ZebraConfig(const std::string &path);

    virtual std::unique_ptr<std::istream> GetStream() const override;

    virtual ConfigurationFileType GetType() const override;
};

}

#endif //QM_MODELS_CFG_ZEBRACONFIG_HPP
