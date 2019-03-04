#include <bits/unique_ptr.h>
#include <functional>
#include <memory>

#include <ns3/data-rate.h>

#include <qm/models.hpp>

namespace qm::models {
void PointToPointConnection::setMtu(const uint16_t t_mtu) {
    m_mtu = ns3::UintegerValue(t_mtu);
}

void PointToPointConnection::setDataRate(const ns3::DataRate t_dataRate) {
    m_dataRate = ns3::DataRateValue(t_dataRate);
}

void PointToPointConnection::setDelay(const ns3::Time t_delay) {
    m_delay = ns3::TimeValue(t_delay);
}

std::map<std::string, std::unique_ptr<ns3::AttributeValue>> PointToPointConnection::GetChannelAttributes() const {
    std::map<std::string, std::unique_ptr<ns3::AttributeValue>> attributesMap{};

    attributesMap["Delay"] = std::unique_ptr<ns3::AttributeValue>(new ns3::TimeValue(m_delay));

    return attributesMap;
}

std::map<std::string, std::unique_ptr<ns3::AttributeValue>> PointToPointConnection::GetDeviceAttributes() const {
    std::map<std::string, std::unique_ptr<ns3::AttributeValue>> attributesMap{};

    attributesMap["DataRate"] = std::unique_ptr<ns3::AttributeValue>(new ns3::DataRateValue(m_dataRate));
    attributesMap["Mtu"] = std::unique_ptr<ns3::AttributeValue>(new ns3::UintegerValue(m_mtu));

    return attributesMap;
}

std::vector<std::shared_ptr<Node>> &PointToPointConnection::GetNodes() {
    return m_nodes;
};
}
