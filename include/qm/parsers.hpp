#ifndef QM_PARSERS_H_
#define QM_PARSERS_H_

#include <array>
#include <cstdint>
#include <unordered_map>
#include "models.hpp"

namespace qm::parsers {

struct ParseException : public std::runtime_error {
    const std::string m_source;

    explicit ParseException(const std::string &message, std::string source) :
            std::runtime_error(message),
            m_source(std::move(source)) {
    }
};
}

#endif

#include "yaml/dto/Index.hpp"
#include "yaml/dto/SimulationConfigurationYamlDTO.hpp"
#include "yaml/dto/ConnectionYamlDTO.hpp"
#include "yaml/dto/NodeYamlDTO.hpp"
#include "yaml/dto/NetworkYamlDTO.hpp"
#include "yaml/dto/ProcessYamlDTO.hpp"
#include "yaml/dto/IpNetworkYamlDTO.hpp"
#include "yaml/dto/IpAddressYamlDTO.hpp"
#include "yaml/parsers/SimulationConfigurationYamlParser.hpp"
#include "yaml/parsers/NS3Types.hpp"
#include "yaml/parsers/Node.hpp"
#include "yaml/parsers/Connection.hpp"
#include "yaml/parsers/Network.hpp"
#include "yaml/parsers/Process.hpp"
#include "yaml/parsers/IpNetwork.hpp"
#include "yaml/parsers/IpAddress.hpp"
#include "yaml/parsers/YamlReference.hpp"

