#ifndef QM_SERVICES_TIMESEQUENCE_H
#define QM_SERVICES_TIMESEQUENCE_H

#include <ns3/nstime.h>
#include <map>

namespace qm::services {
class TimeSequence {
    std::map<std::string, double> m_timers;
    double m_time;
    double m_step;

    double Next();

    double Next(double skip);

    double Current() const;

public:
    TimeSequence();

    ns3::Time NextSeconds();

    ns3::Time NextSeconds(const std::string &nodeId);

    ns3::Time CurrentSeconds();

    ns3::Time CurrentSeconds(const std::string &nodeId);

    void SetSeconds(ns3::Time value);

    void SetSeconds(ns3::Time value, const std::string &nodeId);

    void SetStep(double step);

    void ResetStep();
};
}

#endif //QM_TIMESEQUENCE_H
