#ifndef QM_SERVICES_SIMPLENS3NODECREATOR_HPP
#define QM_SERVICES_SIMPLENS3NODECREATOR_HPP

#include "INs3NodeCreator.hpp"

namespace qm::services {
class SimpleNs3NodeCreator : public INs3NodeCreator {
    void Create(qm::models::Network &network) override;
};
}

#endif //QM_SERVICES_SIMPLENS3NODECREATOR_HPP
