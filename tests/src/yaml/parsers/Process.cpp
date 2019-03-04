#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

TEST_CASE("parse application from valid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
binary: ping
node: !Ref node01
arguments:
 - 127.0.0.1
stackSize: 1048576
startAt: 1s
)");

    const auto actual = yaml.as<qm::yaml::dto::Process>();

    REQUIRE(actual.Binary == "ping");
    REQUIRE(actual.Arguments.size() == 1);
    REQUIRE(actual.Arguments[0] == "127.0.0.1");
    REQUIRE(actual.StackSize == 1048576);
    REQUIRE(actual.NodeReference.Id == "node01");
    REQUIRE(actual.StartAt == ns3::Time::FromDouble(1, ns3::Time::Unit::S));
}

TEST_CASE("parse application from invalid yaml - missing binary", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
node: !Ref node01
arguments:
 - 127.0.0.1
stackSize: 1048576
)");

    REQUIRE_THROWS_AS(yaml.as<qm::yaml::dto::Process>(), qm::ParseException);
    REQUIRE_THROWS_WITH(yaml.as<qm::yaml::dto::Process>(), "'binary' is required for Process");
}

TEST_CASE("parse application from invalid yaml - missing node", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
binary: ping
arguments:
 - 127.0.0.1
stackSize: 1048576
)");

    REQUIRE_THROWS_AS(yaml.as<qm::yaml::dto::Process>(), qm::ParseException);
    REQUIRE_THROWS_WITH(yaml.as<qm::yaml::dto::Process>(), "'node' is required for Process");
}

TEST_CASE("parse application from invalid yaml - invalid arguments", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
binary: ping
node: !Ref node01
arguments: 127.0.0.1
stackSize: 1048576
)");

    REQUIRE_THROWS_AS(yaml.as<qm::yaml::dto::Process>(), qm::ParseException);
    REQUIRE_THROWS_WITH(yaml.as<qm::yaml::dto::Process>(), "'arguments' should be an array");
}
