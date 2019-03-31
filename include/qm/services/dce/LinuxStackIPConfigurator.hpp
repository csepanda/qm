#ifndef QM_SERVICES_DCE_LINUXSTACKIPCONFIGURATOR_H
#define QM_SERVICES_DCE_LINUXSTACKIPCONFIGURATOR_H

#include <qm/services/IpConfigurator.hpp>
#include <qm/services/ApplicationInstaller.hpp>

namespace qm::services::dce {
class LinuxStackIpConfigurator : public IpConfigurator {
    std::shared_ptr<qm::services::ApplicationInstaller> m_appInstaller;
    std::shared_ptr<ns3::DceManagerHelper> m_dceManager;
public:
    LinuxStackIpConfigurator(
      std::shared_ptr<qm::services::ApplicationInstaller> &applicationInstaller,
      std::shared_ptr<ns3::DceManagerHelper> &dceManager);

    void Configure(const qm::models::Network &network) override;

private:
    void RunIp(const std::shared_ptr<qm::models::Node> &node, const std::string &str);

    void AddAddress(const std::shared_ptr<qm::models::Node> &node, const std::string &name,
                    const std::string &address);

    void LinkSet(const std::shared_ptr<qm::models::Node> &node, const std::string &deviceName);
};
}


#endif //QM_SERVICES_DCE_LINUXSTACKIPCONFIGURATOR_H
