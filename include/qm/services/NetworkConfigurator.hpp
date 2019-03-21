#ifndef QM_NETWORKCONFIGURATOR_H
#define QM_NETWORKCONFIGURATOR_H

#include "IpConfigurator.hpp"
#include "INs3NodeCreator.hpp"

namespace qm::services {
class NetworkConfigurator {
    std::unique_ptr<IpConfigurator> m_ipConfigurator;
    std::unique_ptr<INs3NodeCreator> m_ns3NodeCreator;

    void ConfigureP2PConnection(
      const qm::models::Network &network,
      const std::shared_ptr<qm::models::PointToPointConnection> &connection) const;
public:
    NetworkConfigurator(
      qm::models::NetworkStack &,
      std::unique_ptr<INs3NodeCreator> nodeCreator,
      std::shared_ptr<TimeSequence>,
      std::shared_ptr<ns3::DceManagerHelper>
    );

    void Configure(qm::models::Network &network) const;
};
}

#endif //QM_NETWORKCONFIGURATOR_H
