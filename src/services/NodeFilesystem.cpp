#include <sys/stat.h>
#include <linux/limits.h>
#include <dirent.h>
#include <unistd.h>

#include <fstream>

#include <ns3/utils.h>

#include <qm/exceptions.hpp>
#include <qm/services/NodeFilesystem.hpp>
#include <qm/services/utils/FileTypes.hpp>

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

bool NodeFileSystem::DirectoryExists(const std::string &path) {
    const auto realPath = constructRealPath(path);
    struct stat sb{};

    if (::stat(realPath.c_str(), &sb) == 0) {
        utils::FileType fileType = utils::FileTypeUtils::GetFileTypeFor(sb);

        if (fileType == utils::FileType::Directory) {
            return true;
        } else {
            std::stringstream ss{};
            ss << "'" << realPath << "'";
            ss << " is not a directory but: " << utils::FileTypeUtils::ToString(fileType);
            throw qm::IOException(ss.str());
        }
    }

    if (errno == ENOENT) {
        return false;
    }

    std::stringstream ss{};

    ss << "Cannot stat path '" << realPath << "': ";
    ss << strerror(errno);

    throw qm::IOException(ss.str());
}

std::unique_ptr<std::ostream> NodeFileSystem::CreateOutputStream(const std::string &path) {
    const auto realPath = constructRealPath(path);
    const auto stream = new std::ofstream{realPath, std::ofstream::out};

    if (stream->fail()) {
        if (!stream->is_open()) {
            std::stringstream ss{};
            ss << "Cannot open file '" << realPath << "': " << ::strerror(errno);

            throw qm::IOException(ss.str());
        }
    }

    return std::unique_ptr<std::ofstream>(stream);
}

const std::string NodeFileSystem::constructRealPath(const std::string &path) const {
    std::stringstream ss{};

    auto nodeNS3Id = m_node->GetNS3Node()->GetId();
    auto cwd = getCurrentWorkingDirectory();

    ss << cwd << "/" << NS3_DCE_NODE_DIR_PREFIX << nodeNS3Id << path;

    return ss.str();
}

const std::vector<std::string> NodeFileSystem::splitPathToComponents(const std::string &path) const {
    std::stringstream ss {path};
    std::string component;
    std::vector<std::string> components {};

    while (std::getline(ss, component, '/')) {
        components.push_back(component);
    }

    return components;
}

static const std::string getCurrentWorkingDirectory() {
    char buffer[PATH_MAX];

    if (::getcwd(buffer, PATH_MAX) == nullptr) {
        const std::string errStr = strerror(errno);
        throw std::runtime_error("getCurrentWorkingDirectory: " + errStr);
    }

    return std::string{buffer};
}
}
