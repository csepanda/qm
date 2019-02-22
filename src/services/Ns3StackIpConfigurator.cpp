#include <ns3/internet-module.h>
#include <qm/services/IpConfigurator.hpp>

namespace qm::services {

// TODO implement
void Ns3StackIpConfigurator::Configure(const qm::models::Network &network) {
    throw std::logic_error("Not implemented, please use linux kernel stack");
}

};
