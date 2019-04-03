#ifndef QM_SERVICES_MPI_MCLSYSTEMIDMARKERSTRATEGY_HPP
#define QM_SERVICES_MPI_MCLSYSTEMIDMARKERSTRATEGY_HPP

#include <qm/models/Network.hpp>
#include "ISystemIdMarkerStrategy.hpp"

namespace qm::services::mpi {
class MclSystemIdMarkerStrategy : public ISystemIdMarkerStrategy {
    std::map<const std::string, uint32_t> m_systemIds;
public:
    MclSystemIdMarkerStrategy(const models::Network &network, uint32_t systemSize);

    uint32_t GetSystemIdFor(const std::string &nodeId) override;
};

class MclSystemIdMarkerStrategyProducer : public ISystemIdMarkerStrategyProducer {
public:
    std::unique_ptr<ISystemIdMarkerStrategy> Create(const qm::models::Network &network, uint32_t systemSize) override;
};
}

#endif //QM_SERVICES_MPI_MCLSYSTEMIDMARKERSTRATEGY_HPP
