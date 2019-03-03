#include <qm/yaml/parsers/NS3Types.hpp>

namespace YAML {

bool convert<ns3::Time>::decode(const Node &node, ns3::Time &time) {
    time = ns3::Time(node.as<std::string>()); // cannot handle it properly because of NS_FATAL_ERROR
    return true;
}

bool convert<ns3::DataRate>::decode(const Node &node, ns3::DataRate &dataRate) {
    dataRate = ns3::DataRate(node.as<std::string>()); // cannot handle it properly because of NS_FATAL_ERROR
    return true;
}

Node convert<ns3::Time>::encode(const ns3::Time &) {
    throw std::logic_error("Not implemented");
}

Node convert<ns3::DataRate>::encode(const ns3::DataRate &) {
    throw std::logic_error("Not implemented");
}
}
