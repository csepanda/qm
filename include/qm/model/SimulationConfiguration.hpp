//
// Created by cspanda on 2/22/19.
//

#ifndef QM_MODELS_SIMULATIONCONFIGURATION_H
#define QM_MODELS_SIMULATIONCONFIGURATION_H

namespace qm::models {
enum class NetworkStack {
    Ns3,
    LinuxKernel
};

class SimulationConfiguration {
    NetworkStack m_networkStack {NetworkStack::LinuxKernel};

public:
    NetworkStack GetNetworkStack() const;
};
}


#endif //QM_MODELS_SIMULATIONCONFIGURATION_H
