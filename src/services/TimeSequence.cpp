#include <stdexcept>

#include <qm/services/TimeSequence.h>

namespace qm::services {
static const double DEFAULT_TIME_SKIP = 0.001;

TimeSequence::TimeSequence() : m_step{DEFAULT_TIME_SKIP}, m_time{1} {
}

double TimeSequence::Next() {
    return Next(m_step);
}

double TimeSequence::Next(double skip) {
    if (skip <= 0) {
        throw std::invalid_argument("Skip time cannot less than or equal to zero");
    }

    for (const auto &timer : m_timers) {
        if (timer.second > m_time) {
            m_time = timer.second;
        }
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
    m_time += m_step;
}

void TimeSequence::SetStep(double step) {
    if (step <= 0) {
        throw std::invalid_argument("step cannot be less or equal to zero");
    }

    m_step = step;
}

void TimeSequence::ResetStep() {
    m_step = DEFAULT_TIME_SKIP;
}

ns3::Time TimeSequence::CurrentSeconds(const std::string &nodeId) {
    if (m_timers[nodeId] < Current()) {
        m_timers[nodeId] = Current();
    }

    return ns3::Time(m_timers[nodeId]);
}

ns3::Time TimeSequence::NextSeconds(const std::string &nodeId) {
    if (m_timers[nodeId] < Current()) {
        m_timers[nodeId] = Current();
    }

    const auto time = m_timers[nodeId];

    m_timers[nodeId] += m_step;
    return ns3::Time(time);
}

void TimeSequence::SetSeconds(ns3::Time value, const std::string &nodeId) {
    m_timers[nodeId] = value.ToDouble(ns3::Time::Unit::S);
    m_timers[nodeId] += m_step;
}
}
