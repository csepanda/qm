#ifndef QM_SERVICES_MPI_HACSYSTEMIDMARKERSTRATEGY_HPP
#define QM_SERVICES_MPI_HACSYSTEMIDMARKERSTRATEGY_HPP

#include <qm/models/Network.hpp>
#include "ISystemIdMarkerStrategy.hpp"

namespace qm::services::mpi {
class HacSystemIdMarkerStrategy : public ISystemIdMarkerStrategy {
    std::map<const std::string, uint32_t> m_systemIds;
public:
    HacSystemIdMarkerStrategy(const models::Network &network, uint32_t systemSize);

    uint32_t GetSystemIdFor(const std::string &nodeId) override;
};

class HacSystemIdMarkerStrategyProducer : public ISystemIdMarkerStrategyProducer {
public:
    std::unique_ptr<ISystemIdMarkerStrategy> Create(const qm::models::Network &network, uint32_t systemSize) override;
};
}

#endif //QM_SERVICES_MPI_HACSYSTEMIDMARKERSTRATEGY_HPP
