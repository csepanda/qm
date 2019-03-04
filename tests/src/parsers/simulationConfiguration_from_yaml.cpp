#include <catch2/catch.hpp>
#include <qm/parsers.hpp>
#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/SimulationConfiguration.hpp>

std::string createSCValidYaml(const std::string &networkStack);
std::unordered_map<std::string, qm::models::NetworkStack> networkStacksDict = {
  {"linux", qm::models::NetworkStack::LinuxKernel},
  {"ns3", qm::models::NetworkStack::Ns3}
};

TEST_CASE("parse SimulationConfiguration from valid yaml", "[parsers][yaml]") {
    const std::vector<std::string> networkStacks = {"linux", "ns3"};

    for (const auto& ns : networkStacks) {
        const YAML::Node yaml = YAML::Load(createSCValidYaml(ns));
        const auto actual = yaml.as<qm::yaml::dto::SimulationConfiguration>();

        REQUIRE(actual.NetworkStack == networkStacksDict.at(ns));
    }
}

TEST_CASE("parse SimulationConfiguration from invalid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
NetworkStack: foo-bar
)");
    REQUIRE_THROWS(yaml.as<qm::yaml::dto::SimulationConfiguration>());
}

std::string createSCValidYaml(const std::string &networkStack) {
    std::stringstream ss;

    ss << "NetworkStack: " << networkStack << "\n";

    return ss.str();
}

