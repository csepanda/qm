#include <qm/models/ConfigurationFiles/ZebraConfig.hpp>


namespace qm::models::configurations {

std::unique_ptr<std::istream> ZebraConfig::GetStream() const {
    std::unique_ptr<std::stringstream> ss = std::make_unique<std::stringstream>();
    *ss << "hostname zebra" << std::endl
        << "password zebra" << std::endl
        << "log stdout" << std::endl;

    return ss;
}

ConfigurationFileType ZebraConfig::GetType() const {
    return ConfigurationFileType::Zebra;
}
}
