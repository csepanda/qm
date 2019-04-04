#ifndef QM_MODELS_CFG_BGPCONFIG_HPP
#define QM_MODELS_CFG_BGPCONFIG_HPP

#include <qm/models/File.hpp>

namespace qm::models::configurations {
struct BgpNeighbor {
    const std::string IpAddress;
    const uint16_t As;
    const bool NextHopSelf;
    const bool Activated;

    BgpNeighbor(const std::string &IpAddress, uint16_t As, bool nextHopSelf = true, bool activate = true);
};

class BgpConfig : public ConfigurationFile {
    const uint16_t m_as;
    const std::vector<BgpNeighbor> m_neighbors;
public:
    BgpConfig(const std::string &path, uint16_t as, const std::vector<BgpNeighbor> &neighbors);

    uint16_t GetAsNumber() const;

    std::vector<BgpNeighbor> GetNeighbors() const;

    virtual std::unique_ptr<std::istream> GetStream() const override;

    virtual ConfigurationFileType GetType() const override;
};
}

#endif //QM_MODELS_CFG_BGPCONFIG_HPP
