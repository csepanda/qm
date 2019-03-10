#ifndef QM_SERVICES_UTILS_FILEMODE_HPP
#define QM_SERVICES_UTILS_FILEMODE_HPP

#include <sys/stat.h>

namespace qm::services::utils {
class FileModeBuilder {
    mode_t m_mode;
public:
    FileModeBuilder();

    mode_t Build();

    FileModeBuilder &Clear();

    FileModeBuilder &GrantAllToAll();

    FileModeBuilder &GrantReadToAll();

    FileModeBuilder &GrantWriteToAll();

    FileModeBuilder &GrantExecuteToAll();

    FileModeBuilder &GrantSearchToAll();

    FileModeBuilder &GrantAllToOwner();

    FileModeBuilder &GrantReadToOwner();

    FileModeBuilder &GrantWriteToOwner();

    FileModeBuilder &GrantExecuteToOwner();

    FileModeBuilder &GrantSearchToOwner();

    FileModeBuilder &GrantAllToGroup();

    FileModeBuilder &GrantReadToGroup();

    FileModeBuilder &GrantWriteToGroup();

    FileModeBuilder &GrantExecuteToGroup();

    FileModeBuilder &GrantSearchToGroup();

    FileModeBuilder &GrantAllToOthers();

    FileModeBuilder &GrantReadToOthers();

    FileModeBuilder &GrantWriteToOthers();

    FileModeBuilder &GrantExecuteToOthers();

    FileModeBuilder &GrantSearchToOthers();

    FileModeBuilder &SetSUID();

    FileModeBuilder &SetSGID();

    FileModeBuilder &SetRestrictedDeletionFlag();
};
}

#endif //QM_SERVICES_UTILS_FILEMODE_HPP
