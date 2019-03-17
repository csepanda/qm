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
    bool m_mpi{};
    NetworkStack m_networkStack{NetworkStack::LinuxKernel};
    ns3::Time m_stopTime{};

public:
    SimulationConfiguration(NetworkStack networkStack, ns3::Time stopTime, bool enableMpi);

    NetworkStack GetNetworkStack() const;

    ns3::Time GetStopTime() const;
};
}


#endif //QM_MODELS_SIMULATIONCONFIGURATION_H
