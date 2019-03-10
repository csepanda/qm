#include <sys/stat.h>
#include <linux/limits.h>
#include <unistd.h>

#include <fstream>

#include <ns3/utils.h>

#include <qm/exceptions.hpp>
#include <qm/services/NodeFilesystem.hpp>

namespace qm::services {

static const std::string NS3_DCE_NODE_DIR_PREFIX = "files-";
static const std::string getCurrentWorkingDirectory();
NodeFileSystem::NodeFileSystem(const std::shared_ptr<qm::models::Node> &node)
    : m_node{node} {
    if (node->GetNS3Node() == nullptr) {
        throw qm::UninitializedException("NS3 node is not set for node with id: " + node->GetId());
    }
}

void NodeFileSystem::Mkdir(const std::string &path, mode_t mode) {
    const auto realPath = constructRealPath(path);

    int result = ::mkdir(realPath.c_str(), mode);

    if (result < 0) {
        const std::string errStr = strerror(errno);
        throw std::runtime_error("cannot create directory: '" + realPath + "'. Reason: " + errStr);
    }
}

std::unique_ptr<std::ostream> NodeFileSystem::CreateOutputStream(const std::string &path) {
    const auto realPath = constructRealPath(path);
    return std::make_unique<std::ofstream>(realPath, std::ofstream::out);
}

const std::string NodeFileSystem::constructRealPath(const std::string &path) const {
    std::stringstream ss {};

    auto nodeNS3Id = m_node->GetNS3Node()->GetId();
    auto cwd = getCurrentWorkingDirectory();

    ss << cwd << "/" << NS3_DCE_NODE_DIR_PREFIX << nodeNS3Id << "/" << path;

    return ss.str();
}

static const std::string getCurrentWorkingDirectory() {
    char buffer[PATH_MAX];

    if (::getcwd(buffer, PATH_MAX) == nullptr) {
        const std::string errStr = strerror(errno);
        throw std::runtime_error("getCurrentWorkingDirectory: " + errStr);
    }

    return std::string {buffer};
}
}
