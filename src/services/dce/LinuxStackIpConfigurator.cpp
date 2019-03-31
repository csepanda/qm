#include <utility>

#include <utility>

#include <ns3/core-module.h>
#include <ns3/dce-module.h>
#include <qm/services/IpConfigurator.hpp>
#include <qm/services/dce/CommandBuilder.hpp>
#include <qm/services/dce/LinuxStackIPConfigurator.hpp>

namespace qm::services::dce {

static const std::string LIBRARY_ATTRIBUTE = "Library";
static const std::string LIB_LINUX = "liblinux.so";
static const std::string SOCKET_FACTORY = "ns3::LinuxSocketFdFactory";

static const std::string GetSimulatedNetDeviceName(uint32_t ifIndex);

void LinuxStackIpConfigurator::Configure(const qm::models::Network &network) {
    m_dceManager->SetNetworkStack(SOCKET_FACTORY, LIBRARY_ATTRIBUTE, ns3::StringValue(LIB_LINUX));

    for (const auto &node : network.GetNodes()) {
        const auto &ipConfigs = node->GetIpConfigs();

        for (const auto &ipConfig : ipConfigs) {
            const auto &address = ipConfig->Address->GetNetworkStr();
            const auto ifIndex = ipConfig->NS3NetDevice->GetIfIndex();
            const auto devName = GetSimulatedNetDeviceName(ifIndex);

            AddAddress(node, devName, address);
            LinkSet(node, devName);
        }
    }
}

LinuxStackIpConfigurator::LinuxStackIpConfigurator(
  std::shared_ptr<qm::services::ApplicationInstaller> &applicationInstaller,
  std::shared_ptr<ns3::DceManagerHelper> &dceManager
)
  : IpConfigurator(),
    m_appInstaller{applicationInstaller},
    m_dceManager{dceManager} {}

void LinuxStackIpConfigurator::RunIp(const std::shared_ptr<qm::models::Node> &node, const std::string &str) {
    CommandBuilder{m_appInstaller}
      .SetNode(node)
      .SetBinary("ip")
      .SetArguments(str)
      .Execute();
}

void LinuxStackIpConfigurator::AddAddress(
  const std::shared_ptr<qm::models::Node> &node, const std::string &name, const std::string &address) {
    std::ostringstream oss;
    oss << "-f inet addr add " << address << " dev " << name;

    RunIp(node, oss.str());
}

void LinuxStackIpConfigurator::LinkSet(const std::shared_ptr<qm::models::Node> &node, const std::string &deviceName) {
    std::ostringstream oss;
    oss << "link set " << deviceName << " up arp off";

    RunIp(node, oss.str());
}

static const std::string GetSimulatedNetDeviceName(const uint32_t ifIndex) {
    return "sim" + std::to_string(ifIndex);
}
}

