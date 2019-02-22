#ifndef QM_SERVICES_TIMESEQUENCE_H
#define QM_SERVICES_TIMESEQUENCE_H

#include <ns3/nstime.h>

namespace qm::services {
class TimeSequence {
    double m_time;
public:
    double Next();

    ns3::Time NextSeconds();

    double Next(double skip);

    double Current() const;
};
}

#endif //QM_TIMESEQUENCE_H
