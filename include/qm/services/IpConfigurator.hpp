#ifndef QM_SERVICES_IPCONFIGURATOR_H
#define QM_SERVICES_IPCONFIGURATOR_H

#include <ns3/dce-manager-helper.h>
#include <qm/model.hpp>
#include "TimeSequence.h"

namespace qm::services {
class IpConfigurator {

public:
    virtual void Configure(const qm::models::Network &network) = 0;
};

class Ns3StackIpConfigurator : public IpConfigurator {

public:
    void Configure(const qm::models::Network &network) override;
};

}

#endif //QM_SERVICES_IPCONFIGURATOR_H
