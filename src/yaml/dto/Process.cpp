#include <qm/parsers.hpp>
#include <qm/yaml/dto/Process.hpp>

namespace qm::yaml::dto {
std::shared_ptr<qm::models::Process> Process::GetApplication() const {
    if (!NodeReference.Resolved) {
        throw InitializationException("Node reference is not resolved yet!", "Process::GetApplication");
    }

    return std::make_shared<models::Process>(m_node, Binary, StackSize, Arguments, StartAt);
}

void Process::ResolveNode(Network networkYamlDTO) {
    if (NodeReference.Resolved) {
        return;
    }

    try {
        m_node = networkYamlDTO.NodesDTO.at(NodeReference.Id).Node;
        NodeReference.Resolved = true;
    } catch (std::out_of_range &err) {
        std::stringstream ss;
        ss << "Cannot resolve node with id '" << NodeReference.Id << "'";

        auto message = std::move(ss.str());
        ss.str(std::string());
        ss << "for an application";
        auto source = std::move(ss.str());

        throw ParseException(message, std::move(source));
    }
}
}

