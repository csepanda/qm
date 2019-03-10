#ifndef QM_SERVICES_UTILS_NODEFILESYSTEMHELPER_HPP
#define QM_SERVICES_UTILS_NODEFILESYSTEMHELPER_HPP

#include <ns3/string.h>
#include <qm/services/NodeFilesystem.hpp>

namespace qm::services::utils {
class NodeFileSystemHelper {
public:
    static std::string BuildDirectoriesHierarchy(NodeFileSystem &, const std::vector<std::string> &);
};
}

#endif //QM_SERVICES_UTILS_NODEFILESYSTEMHELPER_HPP
