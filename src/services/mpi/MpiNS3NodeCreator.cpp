#include <qm/services/mpi/MpiNS3NodeCreator.hpp>

namespace qm::services::mpi {

MpiNS3NodeCreator::MpiNS3NodeCreator(uint32_t systemId, uint32_t systemSize)
  : m_systemId{systemId},
    m_systemSize{systemSize} {

}

ns3::Ptr<ns3::Node> MpiNS3NodeCreator::Create(const qm::models::Node &node) {
    return ns3::Ptr<ns3::Node>();
}
}
