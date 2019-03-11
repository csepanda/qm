#ifndef QM_FILE_HPP
#define QM_FILE_HPP

#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace qm::models {
enum class FileType {
    Regular
};

class File {
    std::string m_path;
public:
    explicit File(const std::string &path);

    const std::string &GetPath() const;

    virtual FileType GetFileType() const = 0;
};

class RegularFile : public File {
public:
    explicit RegularFile(const std::string &path);

    virtual std::unique_ptr<std::istream> GetStream() const = 0;

    FileType GetFileType() const override;
};

class TextFile : public RegularFile {
    std::vector<std::string> m_lines;
public:
    TextFile(const std::string &path, const std::string &text);

    TextFile(const std::string &path, const std::vector<std::string> &lines);

    virtual std::unique_ptr<std::istream> GetStream() const override;
};
}

#endif //QM_FILE_HPP