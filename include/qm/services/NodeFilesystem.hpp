#ifndef QM_SERVICES_NODEFILESYSTEM_HPP
#define QM_SERVICES_NODEFILESYSTEM_HPP

#include <memory>
#include <qm/models/Node.hpp>

namespace qm::services {
class NodeFileSystem {
    const std::shared_ptr<qm::models::Node> &m_node;

public:
    NodeFileSystem(const std::shared_ptr<qm::models::Node> &node);

    void Mkdir(const std::string &path, mode_t mode);

    bool DirectoryExists(const std::string &path);

    std::unique_ptr<std::ostream> CreateOutputStream(const std::string &path);

private:
    const std::string constructRealPath(const std::string &path) const;
};
}

#endif //QM_SERVICES_NODEFILESYSTEM_HPP
