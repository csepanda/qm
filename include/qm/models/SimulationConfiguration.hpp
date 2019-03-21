#ifndef QM_MODELS_SIMULATIONCONFIGURATION_H
#define QM_MODELS_SIMULATIONCONFIGURATION_H

namespace qm::models {
enum class NetworkStack {
    Ns3,
    LinuxKernel
};

enum class SystemIdMarkerStrategy {
    Manual,
    Mlc
};

class SimulationConfiguration {
    bool m_mpi{};
    SystemIdMarkerStrategy m_systemIdMarkerStrategy{};
    NetworkStack m_networkStack{NetworkStack::LinuxKernel};
    ns3::Time m_stopTime{};

public:
    SimulationConfiguration(
      NetworkStack networkStack,
      ns3::Time stopTime,
      bool enableMpi,
      SystemIdMarkerStrategy m_systemIdMarkerStrategy
    );

    NetworkStack GetNetworkStack() const;

    ns3::Time GetStopTime() const;

    bool IsMpiEnabled() const;

    SystemIdMarkerStrategy GetSystemIdMarkerStrategy() const;
};
}


#endif //QM_MODELS_SIMULATIONCONFIGURATION_H
