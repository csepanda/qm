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
targets:
  - !Ref node01
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

        SECTION("targets") {
            REQUIRE(actual.TargetsRefs.size() == 1);
            REQUIRE(actual.TargetsRefs[0].Id == "node01");
        }
    }
}

TEST_CASE("parse P2P connection from yaml with invalid targets", "[parsers][yaml]") {
    SECTION("targets are not sequence") {
        const YAML::Node node = YAML::Load(R"(
type: p2p
targets: 0
)");
        REQUIRE_THROWS_AS(node.as<qm::parsers::yaml::ConnectionYamlDTO>(), qm::parsers::ParseException);
        REQUIRE_THROWS_WITH(node.as<qm::parsers::yaml::ConnectionYamlDTO>(), "Connection's targets should be a sequence");
    }

    SECTION("targets illegal format") {
        const YAML::Node node = YAML::Load(R"(
type: p2p
targets:
 - !ref node01 123
)");
        REQUIRE_THROWS_AS(node.as<qm::parsers::yaml::ConnectionYamlDTO>(), qm::parsers::ParseException);
        REQUIRE_THROWS_WITH(node.as<qm::parsers::yaml::ConnectionYamlDTO>(), "Expected reference with !Ref tag, got: '!ref'");
    }
}
