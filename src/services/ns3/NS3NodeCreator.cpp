#include <qm/services/ns3/NS3NodeCreator.hpp>

namespace qm::services::ns3 {

::ns3::Ptr<::ns3::Node> NS3NodeCreator::Create(const qm::models::Node &node) {
    return ::ns3::CreateObject<::ns3::Node>();
}
}
