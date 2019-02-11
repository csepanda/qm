#include <qm/model.hpp>

namespace qm::models {

void Node::setNS3Node(ns3::Ptr<ns3::Node> node) {
    ns3_node = node;
};

ns3::Ptr<ns3::Node> Node::getNS3Node() {
    return ns3_node;
}
}