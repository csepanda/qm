#include <vector>
#include <unordered_map>

#include <qm/parsers.hpp>

namespace qm::yaml::dto {
qm::models::Network Network::GetModel() const {
    std::vector<std::shared_ptr<qm::models::Node>> nodes{};
    std::vector<std::shared_ptr<qm::models::Connection>> connections{};

    for (const auto &[_, dto] : NodesDTO) {
        nodes.push_back(dto.Node);
    }
    for (const auto &[_, dto] : ConnectionsDTO) {
        connections.push_back(dto.GetModel());
    }

    return qm::models::Network(nodes, connections);
}
}


