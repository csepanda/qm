#include <qm/services/utils/NodeFileSystemHelper.hpp>
#include <qm/services/utils/FileModeBuilder.hpp>

namespace qm::services::utils {

std::string NodeFileSystemHelper::BuildDirectoriesHierarchy(NodeFileSystem &fs, const std::vector<std::string> &dirs) {
    std::stringstream ss{};

    mode_t mode = FileModeBuilder{}
      .GrantAllToOwner()
      .GrantSearchToGroup()
      .Build();

    for (const auto &dir : dirs) {
        ss << "/" << dir;

        fs.Mkdir(ss.str(), mode);
    }

    return ss.str();
}
}
