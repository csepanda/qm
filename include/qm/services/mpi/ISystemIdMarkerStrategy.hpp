#ifndef QM_SERVICES_MPI_ISYSTEMIDMARKERSTRATEGY_HPP
#define QM_SERVICES_MPI_ISYSTEMIDMARKERSTRATEGY_HPP

#include <cstdint>
#include <qm/models/Node.hpp>

namespace qm::services::mpi {
class ISystemIdMarkerStrategy {
protected:
    const qm::models::Network &m_network;
    const uint32_t m_systemSize{};
public:
    ISystemIdMarkerStrategy(
      const qm::models::Network &network,
      uint32_t systemSize
    ) : m_network{network},
        m_systemSize{systemSize} {
    }

    virtual uint32_t GetSystemIdFor(uint64_t nodeIndex) = 0;
};

class ISystemIdMarkerStrategyProducer {
public:
    virtual std::unique_ptr<ISystemIdMarkerStrategy> Create(const qm::models::Network &network, uint32_t systemSize) = 0;
};
}

#endif //QM_SERVICES_MPI_ISYSTEMIDMARKERSTRATEGY_HPP
