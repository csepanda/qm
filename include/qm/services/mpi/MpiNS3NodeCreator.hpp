#ifndef QM_SERVICES_MPI_MPINS3NODECREATOR_HPP
#define QM_SERVICES_MPI_MPINS3NODECREATOR_HPP

#include <cstdint>
#include <qm/services/INs3NodeCreator.hpp>
#include "ISystemIdMarkerStrategy.hpp"

namespace qm::services::mpi {
class MpiNS3NodeCreator : public INs3NodeCreator {
    uint32_t m_systemId{};
    uint32_t m_systemSize{};
    std::unique_ptr<ISystemIdMarkerStrategyProducer> m_markerStrategyProducer;
public:
    MpiNS3NodeCreator(
      uint32_t systemId,
      uint32_t systemSize,
      std::unique_ptr<ISystemIdMarkerStrategyProducer> markerStrategyProducer
    );

    void Create(qm::models::Network &network) override;
};
}

#endif //QM_SERVICES_MPI_MPINS3NODECREATOR_HPP
