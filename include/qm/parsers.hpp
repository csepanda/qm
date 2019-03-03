#ifndef QM_PARSERS_H_
#define QM_PARSERS_H_

#include <array>
#include <cstdint>
#include <unordered_map>
#include "model.hpp"

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
#include "yaml/ip.hpp"
#include "yaml/p2p_connection.hpp"
#include "yaml/node.hpp"
#include "yaml/yaml_reference.hpp"
#include "yaml/network.hpp"
#include "yaml/dto.h"
#include "qm/yaml/ProcessYamlDTO.hpp"
#include "yaml/dto/SimulationConfigurationYamlDTO.hpp"
#include "yaml/parsers/SimulationConfigurationYamlParser.hpp"
#include "yaml/parsers/NS3Types.hpp"

