//
// Created by cspanda on 3/3/19.
//

#ifndef QM_NETWORKCONFIGURATOR_H
#define QM_NETWORKCONFIGURATOR_H

#include "IpConfigurator.hpp"

namespace qm::services {
class NetworkConfigurator {
    std::unique_ptr<qm::services::IpConfigurator> m_ipConfigurator;
    std::shared_ptr<TimeSequence> m_timer;

    void ConfigureP2PConnection(const qm::models::Network& network, const std::shared_ptr<qm::models::PointToPointConnection> &connection) const;
public:
    NetworkConfigurator(
      qm::models::NetworkStack &,
      std::shared_ptr<TimeSequence>,
      std::shared_ptr<ns3::DceManagerHelper>
    );

    void Configure(qm::models::Network& network) const;
};
}

#endif //QM_NETWORKCONFIGURATOR_H
