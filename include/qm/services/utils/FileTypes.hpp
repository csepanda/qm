#ifndef QM_SERVICES_UTILS_FILETYPES_HPP
#define QM_SERVICES_UTILS_FILETYPES_HPP

#include <string>
#include <sys/stat.h>

namespace qm::services::utils {
enum class FileType {
    RegularFile,
    Directory,
    CharacterDevice,
    BlockDevice,
    Pipe,
    SymbolicLink,
    Socket,
    Unknown
};

struct FileTypeUtils {
    static FileType GetFileTypeFor(struct stat &sb);
    static std::string ToString(FileType fileType);
};
}

#endif //QM_SERVICES_UTILS_FILETYPES_HPP
