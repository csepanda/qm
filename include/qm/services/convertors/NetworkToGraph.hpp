#ifndef QM_SERVICES_CONVERTORS_NETWORKTOGRAPH_HPP
#define QM_SERVICES_CONVERTORS_NETWORKTOGRAPH_HPP

#include <qm/algorithm/graph/Graph.hpp>
#include <qm/models/Node.hpp>
#include <qm/models/Network.hpp>

namespace qm::services::convertors {

typedef qm::algorithm::graph::Vertex<qm::models::Node, qm::models::Connection> NetworkVertex;
typedef qm::algorithm::graph::Edge<qm::models::Node, qm::models::Connection> NetworkEdge;
typedef qm::algorithm::graph::Graph<qm::models::Node, qm::models::Connection> NetworkGraph;

NetworkGraph ConvertNetworkToGraph(const qm::models::Network &network);

int GetWeightFor(const std::shared_ptr<qm::models::Node> &node);
int GetWeightFor(const std::shared_ptr<qm::models::Connection> &connection);

}

#endif //QM_SERVICES_CONVERTORS_NETWORKTOGRAPH_HPP
