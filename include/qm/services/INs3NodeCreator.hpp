#ifndef QM_SERVICES_INODECREATOR_HPP
#define QM_SERVICES_INODECREATOR_HPP

#include <ns3/node.h>
#include <qm/models/Network.hpp>

namespace qm::services {
class INs3NodeCreator {
public:
    virtual void Create(qm::models::Network &network) = 0;
};
}

#endif //QM_SERVICES_INODECREATOR_HPP
