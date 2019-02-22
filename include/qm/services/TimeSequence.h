#ifndef QM_SERVICES_TIMESEQUENCE_H
#define QM_SERVICES_TIMESEQUENCE_H

namespace qm::services {
class TimeSequence {
    double m_time;
public:
    double Next();

    double Next(double skip);

    double Current() const;
};
}

#endif //QM_TIMESEQUENCE_H
