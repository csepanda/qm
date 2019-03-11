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
    m_lines{} {
    m_lines.push_back(text);
}

TextFile::TextFile(const std::string &path, const std::vector<std::string> &lines)
  : RegularFile(path),
    m_lines{lines} {
}

std::unique_ptr<std::istream> TextFile::GetStream() const {
    auto *ss = new std::stringstream();

    std::copy(
      m_lines.begin(),
      m_lines.end(),
      std::ostream_iterator<std::string>(*ss, "\n")
    );

    return std::unique_ptr<std::istream>(ss);
}

}
