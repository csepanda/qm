//
// Created by cspanda on 2/22/19.
//

#ifndef QM_SERVICES_DCE_LINUXSTACKIPCONFIGURATOR_H
#define QM_SERVICES_DCE_LINUXSTACKIPCONFIGURATOR_H

#include <qm/services/IpConfigurator.hpp>

namespace qm::services::dce {
class LinuxStackIpConfigurator : public IpConfigurator {
    std::shared_ptr <qm::services::TimeSequence> m_timer;
    std::shared_ptr <ns3::DceManagerHelper> m_dceManager;
public:
    LinuxStackIpConfigurator(std::shared_ptr <qm::services::TimeSequence> &timer,
                             std::shared_ptr <ns3::DceManagerHelper> &dceManager) : m_timer{timer},
                                                                                    m_dceManager{dceManager} {}

    void Configure(const qm::models::Network &network) override;
};
}


#endif //QM_SERVICES_DCE_LINUXSTACKIPCONFIGURATOR_H
