#include <stdexcept>

#include <qm/services/TimeSequence.h>

namespace qm::services {
static const double DEFAULT_TIME_SKIP = 0.1;

double TimeSequence::Next() {
    return Next(DEFAULT_TIME_SKIP);
}

double TimeSequence::Next(double skip) {
    if (skip <= 0) {
        throw std::invalid_argument("Skip time cannot less than or equal to zero");
    }

    const auto time = m_time;

    m_time += skip;
    return time;
}

double TimeSequence::Current() const {
    return m_time;
}

ns3::Time TimeSequence::NextSeconds() {
    return ns3::Seconds(Next());
}

ns3::Time TimeSequence::CurrentSeconds() {
    return ns3::Seconds(Current());
}

void TimeSequence::SetSeconds(ns3::Time value) {
    m_time = value.ToDouble(ns3::Time::Unit::S);
    m_time += DEFAULT_TIME_SKIP;
}
}
