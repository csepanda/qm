#ifndef QM_SERVICES_INODECREATOR_HPP
#define QM_SERVICES_INODECREATOR_HPP

#include <ns3/node.h>
#include <qm/models/Node.hpp>

namespace qm::services {
class INodeCreator {
public:
    virtual ns3::Ptr<ns3::Node> Create(const qm::models::Node &node) = 0;
};
}

#endif //QM_SERVICES_INODECREATOR_HPP
