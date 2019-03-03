#include <utility>

#include <ns3/core-module.h>
#include <ns3/dce-module.h>
#include <qm/services/IpConfigurator.hpp>
#include <qm/services/dce/CommandBuilder.hpp>
#include <qm/services/dce/LinuxStackIPConfigurator.hpp>

namespace qm::services::dce {

static const std::string LIBRARY_ATTRIBUTE = "Library";
static const std::string LIB_LINUX = "liblinux.so";
static const std::string SOCKET_FACTORY = "ns3::LinuxSocketFactory";

static const std::string GetSimulatedNetDeviceName(uint32_t ifIndex);

static void RunIp(const ns3::Ptr<ns3::Node> &node, ns3::Time at, const std::string &str);
static void AddAddress(const ns3::Ptr<ns3::Node> &node, ns3::Time at, const std::string &name, const std::string &address);
static void LinkSet(const ns3::Ptr<ns3::Node> &node, ns3::Time at, const std::string &deviceName);

void LinuxStackIpConfigurator::Configure(const qm::models::Network &network) {
    m_dceManager->SetNetworkStack(SOCKET_FACTORY, LIBRARY_ATTRIBUTE, ns3::StringValue(LIB_LINUX));

    for (const auto &node : network.GetNodes()) {
        const auto &ns3Node = node->GetNS3Node();
        const auto &ipConfigs = node->GetIpConfigs();

        for (const auto &ipConfig : ipConfigs) {
            const auto &address = ipConfig->Address->GetNetworkStr();
            const auto ifIndex = ipConfig->NS3NetDevice->GetIfIndex();
            const auto devName = GetSimulatedNetDeviceName(ifIndex);

            AddAddress(ns3Node, m_timer->NextSeconds(), devName, address);
            LinkSet(ns3Node, m_timer->NextSeconds(), devName);
        }
    }
}

static void RunIp(const ns3::Ptr<ns3::Node> &node, ns3::Time at, const std::string &str) {
    CommandBuilder{node}
      .SetBinary("ip")
      .SetArguments(str)
      .Execute(std::move(at));
}

static void AddAddress(const ns3::Ptr<ns3::Node> &node, ns3::Time at, const std::string &name, const std::string &address) {
    std::ostringstream oss;
    oss << "-f inet addr add " << address << " dev " << name;

    RunIp(node, std::move(at), oss.str());
}

static void LinkSet(const ns3::Ptr<ns3::Node> &node, ns3::Time at, const std::string &deviceName) {
    std::ostringstream oss;
    oss << "link set " << deviceName << "up arp off";

    RunIp(node, std::move(at), oss.str());
}

static const std::string GetSimulatedNetDeviceName(const uint32_t ifIndex) {
    return "sim" + std::to_string(ifIndex);
}
}

