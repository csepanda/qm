#include <qm/services/FilesInstaller.hpp>
#include <qm/services/NodeFilesystem.hpp>
#include <qm/exceptions.hpp>

namespace qm::services {

void FilesInstaller::Install(const std::vector<std::shared_ptr<qm::models::Node>> &nodes) {
    for (const auto &node : nodes) {
        InstallOne(node);
    }

}

void FilesInstaller::InstallOne(const std::shared_ptr<qm::models::Node> &node) {
    const auto &files = node->GetFiles();

    if (files.empty()) {
        return;
    }

    NodeFileSystem fs{node};

    for (const auto &file : files) {
        try {
            const auto fileType = file->GetFileType();
            switch (fileType) {
                case models::FileType::Regular: {
                    const auto ptr = file.get();
                    InstallRegularFile(fs, dynamic_cast<qm::models::RegularFile *>(ptr));
                    break;
                }
                default:
                    throw std::logic_error(
                      "Handler for this FileType is not implemented " + std::to_string((int) fileType));
            }
        } catch (qm::IOException &ioException) {
            std::stringstream ss{};

            ss << "File installation for node (id: '" << node->GetId() << "') is failed with I/O error:\n";
            ss << ioException.what();
            ss << "\nVirtual path is: " << file->GetPath();
            throw IOException(ss.str());
        }
    }
}

void FilesInstaller::InstallRegularFile(NodeFileSystem &fs, const qm::models::RegularFile *file) {
    const size_t buffer_size = 4096;
    const auto out = fs.CreateOutputStream(file->GetPath());
    const auto in = file->GetStream();

    char buffer[4096];

    while (!in->eof()) {
        in->read(buffer, buffer_size);

        if (in->bad()) {
            throw qm::IOException("fail at read data for regular file");

        }

        out->write(buffer, in->gcount());

        if (out->bad()) {
            throw qm::IOException("fail at write data for regular file");
        }
    }
}


}

