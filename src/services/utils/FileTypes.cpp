#include <qm/services/utils/FileTypes.hpp>
#include <stdexcept>

namespace qm::services::utils {

FileType FileTypeUtils::GetFileTypeFor(struct stat &sb) {
    mode_t mode = sb.st_mode;

    if (S_ISREG(mode)) {
        return FileType::RegularFile;
    } else if (S_ISDIR(mode)) {
        return FileType::Directory;
    } else if (S_ISCHR(mode)) {
        return FileType::CharacterDevice;
    } else if (S_ISBLK(mode)) {
        return FileType::BlockDevice;
    } else if (S_ISFIFO(mode)) {
        return FileType::Pipe;
    } else if (S_ISSOCK(mode)) {
        return FileType::Socket;
    } else if (S_ISLNK(mode)) {
        return FileType::SymbolicLink;
    }
    return FileType::Unknown;
}

std::string FileTypeUtils::ToString(FileType fileType) {
    switch (fileType) {
        case FileType::RegularFile:
            return "RegularFile";
        case FileType::Directory:
            return "Directory";
        case FileType::CharacterDevice:
            return "CharacterDevice";
        case FileType::BlockDevice:
            return "BlockDevice";
        case FileType::Pipe:
            return "Pipe";
        case FileType::SymbolicLink:
            return "SymbolicLink";
        case FileType::Socket:
            return "Socket";
        case FileType::Unknown:
            return "Unknown";
        default:
            throw std::invalid_argument("Unknown fileType value: " + std::to_string((int) fileType));
    }
}
}
