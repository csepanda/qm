#include <qm/services/utils/FileModeBuilder.hpp>

namespace qm::services::utils {

FileModeBuilder::FileModeBuilder() : m_mode {0} {
}

mode_t FileModeBuilder::Build() {
    return m_mode;
}

FileModeBuilder &FileModeBuilder::Clear() {
    m_mode = 0;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantAllToAll() {
    m_mode |= S_IRWXU | S_IRWXG | S_IRWXO;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantReadToAll() {
    m_mode |= S_IRUSR | S_IRGRP | S_IROTH;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantWriteToAll() {
    m_mode |= S_IWUSR | S_IWGRP | S_IWOTH;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantExecuteToAll() {
    m_mode |= S_IXUSR | S_IXGRP | S_IXOTH;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantSearchToAll() {
    return this->GrantExecuteToAll();
}

FileModeBuilder &FileModeBuilder::GrantAllToOwner() {
    m_mode |= S_IRWXU;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantReadToOwner() {
    m_mode |= S_IRUSR;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantWriteToOwner() {
    m_mode |= S_IWUSR;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantExecuteToOwner() {
    m_mode |= S_IXUSR;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantSearchToOwner() {
    return this->GrantExecuteToOwner();
}

FileModeBuilder &FileModeBuilder::GrantAllToGroup() {
    m_mode |= S_IRWXG;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantReadToGroup() {
    m_mode |= S_IRGRP;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantWriteToGroup() {
    m_mode |= S_IWGRP;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantExecuteToGroup() {
    m_mode |= S_IXGRP;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantSearchToGroup() {
    return this->GrantExecuteToGroup();
}

FileModeBuilder &FileModeBuilder::GrantAllToOthers() {
    m_mode |= S_IRWXO;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantReadToOthers() {
    m_mode |= S_IROTH;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantWriteToOthers() {
    m_mode |= S_IWOTH;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantExecuteToOthers() {
    m_mode |= S_IXOTH;
    return *this;
}

FileModeBuilder &FileModeBuilder::GrantSearchToOthers() {
    return this->GrantExecuteToOthers();
}

FileModeBuilder &FileModeBuilder::SetSUID() {
    m_mode |= S_ISUID;
    return *this;
}

FileModeBuilder &FileModeBuilder::SetSGID() {
    m_mode |= S_ISGID;
    return *this;
}

FileModeBuilder &FileModeBuilder::SetRestrictedDeletionFlag() {
    m_mode |= S_ISVTX;
    return *this;
}
}

