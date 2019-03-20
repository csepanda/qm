#include <qm/services/SimpleNs3NodeCreator.hpp>

namespace qm::services {

void SimpleNs3NodeCreator::Create(qm::models::Network &network) {
    for (auto &node : network.GetNodes()) {
        node->SetNS3Node(ns3::CreateObject<ns3::Node>());
    }
}
}
