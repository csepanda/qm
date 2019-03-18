#ifndef QM_SERVICES_MPI_MPINS3NODECREATOR_HPP
#define QM_SERVICES_MPI_MPINS3NODECREATOR_HPP

#include <cstdint>
#include <qm/services/INodeCreator.hpp>

namespace qm::services::mpi {
class MpiNS3NodeCreator : public INodeCreator {
    uint32_t m_systemId{};
    uint32_t m_systemSize{};
public:
    MpiNS3NodeCreator(uint32_t systemId, uint32_t systemSize);

    ns3::Ptr<ns3::Node> Create(const qm::models::Node &node) override;
};
}

#endif //QM_SERVICES_MPI_MPINS3NODECREATOR_HPP
