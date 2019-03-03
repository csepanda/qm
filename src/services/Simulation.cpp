#include <algorithm>
#include <utility>

#include <ns3/node-container.h>
#include <ns3/point-to-point-helper.h>

#include <qm/exceptions.hpp>
#include <qm/model.hpp>
#include <qm/services/dce/LinuxStackIPConfigurator.hpp>
#include <qm/services/Simulation.hpp>

namespace qm::services {

Simulation::Simulation(
  const qm::models::SimulationConfiguration cfg,
  qm::models::Network network,
  std::vector<std::shared_ptr<qm::models::Application>> applications,
  std::shared_ptr<TimeSequence> timer)

  : m_network{std::move(network)},
    m_applications{std::move(applications)} {

    m_dceManager = std::make_shared<ns3::DceManagerHelper>();

    switch (cfg.GetNetworkStack()) {
        case models::NetworkStack::Ns3:
            m_ipConfigurator = std::make_unique<Ns3StackIpConfigurator>();
            break;
        case models::NetworkStack::LinuxKernel:
            m_ipConfigurator = std::make_unique<qm::services::dce::LinuxStackIpConfigurator>(timer, m_dceManager);
            break;
    }
}

void Simulation::ConfigureNetwork() {
    for (const auto &node : m_network.GetNodes()) {
        node->SetNS3Node(ns3::CreateObject<ns3::Node>());
    }

    for (const auto &connection : m_network.GetConnections()) {
        switch (connection->GetConnectionType()) {
            case qm::models::ConnectionType::P2P: {
                const auto p2pConnection = std::dynamic_pointer_cast<qm::models::PointToPointConnection>(connection);

                this->ConfigureP2PConnection(p2pConnection);
                break;
            }
            default:
                throw InitializationException("", "");
        }
    }

    m_ipConfigurator->Configure(m_network);
}

void Simulation::ConfigureP2PConnection(const std::shared_ptr<qm::models::PointToPointConnection> &connection) {
    ns3::NodeContainer net{};

    const auto nodes = connection->GetNodes();

    if (nodes.size() != 2) {
        throw InitializationException("P2P connection cannot handle less or greater than 2 nodes",
                                      "P2PConnection::Initialization");
    }

    for (const auto &node : nodes) {
        if (node == nullptr) {
            throw InitializationException("Node must be not null", "P2PConnection::Initialization");
        }
        net.Add(node->GetNS3Node());
    }

    ns3::PointToPointHelper helper{};

    const auto netDevicesContainer = helper.Install(net);

    for (auto it = netDevicesContainer.Begin(); it != netDevicesContainer.End(); ++it) {
        const auto &netDevice = *it;
        const auto ns3Node = netDevice->GetNode();
        const auto &node = m_network.FindNode(ns3Node);
        const auto &ipConfig = node->FindIpConfig(connection);

        ipConfig->NS3NetDevice = netDevice;
    }
}
}
