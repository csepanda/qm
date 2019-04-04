#include <qm/models/File.hpp>
#include <cstring>
#include <iterator>

namespace qm::models {

File::File(const std::string &path)
  : m_path{path} {
}

const std::string &File::GetPath() const {
    return m_path;
}

RegularFile::RegularFile(const std::string &path) : File(path) {
}

FileType RegularFile::GetFileType() const {
    return FileType::Regular;
}

TextFile::TextFile(const std::string &path, const std::string &text)
  : RegularFile(path),
    m_text {text} {
}
std::unique_ptr<std::istream> TextFile::GetStream() const {
    return std::unique_ptr<std::istream>(new std::stringstream {m_text});
}

ConfigurationFile::ConfigurationFile(const std::string &path) : RegularFile(path) {}
}
