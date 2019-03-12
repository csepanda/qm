#ifndef QM_SERVICES_FILESINSTALLER_HPP
#define QM_SERVICES_FILESINSTALLER_HPP

#include <qm/models/Node.hpp>
#include "NodeFilesystem.hpp"

namespace qm::services {
class FilesInstaller {
public:
    void Install(const std::vector<std::shared_ptr<qm::models::Node>> &nodes);

private:
    void InstallOne(const std::shared_ptr<qm::models::Node> &node);
    void InstallRegularFile(NodeFileSystem &fs, const qm::models::RegularFile *file);
};
}

#endif //QM_SERVICES_FILESINSTALLER_HPP
