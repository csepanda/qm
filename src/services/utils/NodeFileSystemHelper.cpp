#include <qm/services/utils/NodeFileSystemHelper.hpp>
#include <qm/services/utils/FileModeBuilder.hpp>

namespace qm::services::utils {

std::string NodeFileSystemHelper::BuildDirectoriesHierarchy(NodeFileSystem &fs, const std::vector<std::string> &dirs) {
    std::stringstream ss{};

    mode_t mode = FileModeBuilder{}
      .GrantAllToOwner()
      .GrantReadToGroup()
      .GrantSearchToGroup()
      .Build();

    for (const auto &dir : dirs) {
        ss << "/" << dir;

        const auto pathname = ss.str();
        if (!fs.DirectoryExists(pathname)) {
            fs.Mkdir(pathname, mode);
        }
    }

    return ss.str();
}
}
