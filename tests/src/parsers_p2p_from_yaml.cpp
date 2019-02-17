#include <catch2/catch.hpp>
#include <qm/parsers.hpp>
#include <yaml-cpp/yaml.h>

TEST_CASE("parse P2P connection from valid yaml", "[parsers][yaml]") {
    SECTION("default") {
        const YAML::Node node = YAML::Load(R"(type: p2p)");
        const auto actual = node.as<qm::parsers::yaml::ConnectionYamlDTO>();

        REQUIRE(actual.type == qm::models::ConnectionType::P2P);
    }

    SECTION("set attributes") {
        const YAML::Node node = YAML::Load(R"(
type: p2p
dataRate: 1Mbps
mtu: 1500
delay: 100ms
)");
        const auto actual = node.as<qm::parsers::yaml::ConnectionYamlDTO>();
        const auto deviceAttributes = actual.p2p->GetDeviceAttributes();
        const auto channelAttributes = actual.p2p->GetChannelAttributes();

        SECTION("data rate") {
            const ns3::DataRateValue *dataRateValue = dynamic_cast<ns3::DataRateValue *>(deviceAttributes.at(
              "DataRate").get());

            REQUIRE(dataRateValue->Get().GetBitRate() == 1000 * 1000);
        }

        SECTION("mtu") {
            const ns3::UintegerValue *mtuValue = dynamic_cast<ns3::UintegerValue *>(deviceAttributes.at("Mtu").get());

            REQUIRE(mtuValue->Get() == 1500);
        }

        SECTION("mtu") {
            const ns3::TimeValue *delay = dynamic_cast<ns3::TimeValue *>(channelAttributes.at("Delay").get());

            REQUIRE(delay->Get().GetMilliSeconds() == 100);
        }
    }
}
