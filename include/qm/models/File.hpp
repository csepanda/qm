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
    std::string m_text;
public:
    TextFile(const std::string &path, const std::string &text);

    virtual std::unique_ptr<std::istream> GetStream() const override;
};

enum class ConfigurationFileType {
    Zebra,
    Bgp
};

class ConfigurationFile : public RegularFile {
public:
    explicit ConfigurationFile(const std::string &path);

    virtual ConfigurationFileType GetType() const = 0;
};

}

#endif //QM_FILE_HPP
