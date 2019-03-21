#include <utility>


#include <qm/services/dce/LinuxStackIPConfigurator.hpp>
#include <qm/services/NetworkConfigurator.hpp>
#include <qm/exceptions.hpp>
#include <ns3/point-to-point-helper.h>
#include <qm/services/SimpleNs3NodeCreator.hpp>
#include <qm/services/mpi/ManualSystemIdMarkerStrategy.hpp>

namespace qm::services {

NetworkConfigurator::NetworkConfigurator(
  qm::models::NetworkStack &networkStack,
  std::unique_ptr<INs3NodeCreator> nodeCreator,
  std::shared_ptr<TimeSequence> timer,
  std::shared_ptr<ns3::DceManagerHelper> dceManager
) {
    switch (networkStack) {
        case models::NetworkStack::Ns3:
            m_ipConfigurator = std::make_unique<Ns3StackIpConfigurator>();
            break;
        case models::NetworkStack::LinuxKernel:
            m_ipConfigurator = std::make_unique<qm::services::dce::LinuxStackIpConfigurator>(timer, dceManager);
            break;
    }

    m_ns3NodeCreator = std::move(nodeCreator);
}

inline static const auto NC_CONFIGURE_SOURCE = "NetworkConfigurator::Configure";

void NetworkConfigurator::Configure(qm::models::Network &network) const {
    m_ns3NodeCreator->Create(network);

    for (const auto &connection : network.GetConnections()) {
        switch (connection->GetConnectionType()) {
            case qm::models::ConnectionType::P2P: {
                const auto p2pConnection = std::dynamic_pointer_cast<qm::models::PointToPointConnection>(connection);

                this->ConfigureP2PConnection(network, p2pConnection);
                break;
            }
            default:
                throw InitializationException("Unsupported connection type", NC_CONFIGURE_SOURCE);
        }
    }

    m_ipConfigurator->Configure(network);
}

inline static const auto NC_P2P_SOURCE = "NetworkConfigurator::ConfigureP2PConnection";

void NetworkConfigurator::ConfigureP2PConnection(
  const qm::models::Network &network,
  const std::shared_ptr<qm::models::PointToPointConnection> &connection
) const {

    ns3::NodeContainer net{};

    const auto nodes = connection->GetNodes();

    if (nodes.size() != 2) {
        throw InitializationException("P2P connection cannot handle less or greater than 2 nodes", NC_P2P_SOURCE);
    }

    for (const auto &node : nodes) {
        if (node == nullptr) {
            throw InitializationException("Node must be not null", NC_P2P_SOURCE);
        }
        net.Add(node->GetNS3Node());
    }

    ns3::PointToPointHelper helper{};

    const auto netDevicesContainer = helper.Install(net);

    for (auto it = netDevicesContainer.Begin(); it != netDevicesContainer.End(); ++it) {
        const auto &netDevice = *it;
        const auto ns3Node = netDevice->GetNode();
        const auto &node = network.FindNode(ns3Node);
        const auto &ipConfig = node->FindIpConfig(connection);

        ipConfig->NS3NetDevice = netDevice;
    }

    // helper.EnablePcapAll("simulation-p2p");
}
};
