#include <iostream>

#include <yaml-cpp/yaml.h>

#include <qm/models.hpp>
#include <qm/services/Simulation.hpp>
#include <qm/services/SimulationProducer.hpp>
#include <qm/parsers.hpp>

int main(int argc, char **argv) {
    if (argc < 2) {
        return 2;
    }

    const auto cfgFile = argv[1];
    const auto yaml = YAML::LoadFile(cfgFile);

    const auto simulationConfiguration = yaml["simulationConfiguration"].as<qm::yaml::dto::SimulationConfiguration>().GetModel();
    auto network = yaml["network"].as<qm::yaml::dto::Network>();
    auto applications = yaml["applications"].as<std::vector<qm::yaml::dto::Process>>();

    std::vector<std::shared_ptr<qm::models::Process>> processes{};
    for (qm::yaml::dto::Process &dto : applications) {
        dto.ResolveNode(network);
        processes.push_back(std::move(dto.GetModel()));
    }

    qm::services::SimulationProducer simulationProducer {simulationConfiguration};

    qm::services::Simulation sim = simulationProducer.Create(network.GetModel(), processes);

    sim.Run();

    return 0;
}

