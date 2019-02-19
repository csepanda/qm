#include <qm/parsers.hpp>

namespace qm::parsers::yaml {

using ConnectionPtr = std::shared_ptr<qm::models::Connection>;
using ConnectionsDictionary = std::unordered_map<std::string, ConnectionYamlDTO>;

static void
inverseResolve(std::string &referrerId, std::string &targetId, std::vector<YamlReference> &targetRefs);

static ConnectionPtr
resolveConnectionRef(std::string &referrerId, YamlReference &reference, ConnectionsDictionary &connectionsDTO);

void NetworkYamlDTO::ResolveContext() {
    // resolve references between ip-configs and connections
    // in terms of network it's actually resolving network interface and corresponding channel
    for (auto& [id, nodeDTO] : NodesDTO) {
        auto nodeId = nodeDTO.Node->GetId();
        auto &ipConfigs = nodeDTO.IpConfigs;

        for (IpConfigYamlDTO &configDTO : ipConfigs) {
            auto &connectionRef = configDTO.ConnectionRef;
            auto connection = resolveConnectionRef(nodeId, configDTO.ConnectionRef, ConnectionsDTO);

            configDTO.IpConfig.BindConnection = connection;
            connection->GetNodes().push_back(nodeDTO.Node);

            nodeDTO.Node->AddIpConfig(configDTO.IpConfig);
        }
    }
}

static ConnectionPtr
resolveConnectionRef(std::string &referrerId, YamlReference &reference, ConnectionsDictionary &connectionsDTO) {
    try {
        ConnectionYamlDTO &connection = connectionsDTO.at(reference.Id);

        inverseResolve(referrerId, reference.Id, connection.TargetsRefs);
        reference.Resolved = true;
        return connection.GetConnection();
    } catch (std::out_of_range &err) {
        std::stringstream ss;
        ss << "Cannot resolve connection with id '" << reference.Id << "'";

        auto message = std::move(ss.str());
        ss.str(std::string());
        ss << "for object with id '" << referrerId << "'";
        auto source = std::move(ss.str());

        throw ParseException(message, std::move(source));
    }
}

static void inverseResolve(std::string &referrerId, std::string &targetId, std::vector<YamlReference> &targetRefs) {
    int refsCount = 0;
    YamlReference *backRef = nullptr;
    for (auto &ref : targetRefs) {
        if (ref.Id == referrerId) {
            backRef = &ref;
            refsCount++;
            if (!ref.Resolved) {
                break;
            }
        }
    }

    if (backRef == nullptr) {
        std::stringstream ss;
        ss << "Object with id '" << targetId << "' has no back reference";

        auto message = std::move(ss.str());
        ss.str(std::string());
        ss << "for object with id '" << referrerId;
        auto source = std::move(ss.str());

        throw ParseException(message, std::move(source));
    }

    if (backRef->Resolved) {
        std::stringstream ss;
        ss << "Found " << refsCount << " already resolved refs of object with id '" << targetId << "'";

        auto message = std::move(ss.str());
        ss.str(std::string());
        ss << "for object with id '" << referrerId;
        auto source = std::move(ss.str());

        throw ParseException(message, std::move(source));
    }

    backRef->Resolved = true;
}

}
