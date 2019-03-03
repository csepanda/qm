#ifndef QM_YAML_PARSERS_NS3VALUES_H
#define QM_YAML_PARSERS_NS3VALUES_H

#include <ns3/nstime.h>
#include <ns3/data-rate.h>

#include <yaml-cpp/yaml.h>

namespace YAML {
template<>
struct convert<ns3::Time> {
    static Node encode(const ns3::Time&);

    static bool decode(const Node &node, ns3::Time&);
};

template<>
struct convert<ns3::DataRate> {
    static Node encode(const ns3::DataRate &);

    static bool decode(const Node &node, ns3::DataRate &);
};

}

#endif //QM_YAML_PARSERS_NS3VALUES_H
