#ifndef QM_SERVICES_NS3_NS3NODECREATOR_HPP
#define QM_SERVICES_NS3_NS3NODECREATOR_HPP

#include <qm/services/INodeCreator.hpp>

namespace qm::services::ns3 {
class NS3NodeCreator : public INodeCreator {
public:
    ::ns3::Ptr<::ns3::Node> Create(const qm::models::Node &node) override;
};
}

#endif //QM_SERVICES_NS3_NS3NODECREATOR_HPP
