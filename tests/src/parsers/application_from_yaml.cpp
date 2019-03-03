#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

TEST_CASE("parse application from valid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
binary: ping
node: !Ref node01
arguments:
 - 127.0.0.1
stackSize: 1048576
)");

    const auto actual = yaml.as<qm::parsers::yaml::ApplicationYamlDTO>();

    REQUIRE(actual.Binary == "ping");
    REQUIRE(actual.Arguments.size() == 1);
    REQUIRE(actual.Arguments[0] == "127.0.0.1");
    REQUIRE(actual.StackSize == 1048576);
    REQUIRE(actual.NodeReference.Id == "node01");
}

TEST_CASE("parse application from invalid yaml - missing binary", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
node: !Ref node01
arguments:
 - 127.0.0.1
stackSize: 1048576
)");

    REQUIRE_THROWS_AS(yaml.as<qm::parsers::yaml::ApplicationYamlDTO>(), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(yaml.as<qm::parsers::yaml::ApplicationYamlDTO>(), "'binary' is required for Application");
}

TEST_CASE("parse application from invalid yaml - missing node", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
binary: ping
arguments:
 - 127.0.0.1
stackSize: 1048576
)");

    REQUIRE_THROWS_AS(yaml.as<qm::parsers::yaml::ApplicationYamlDTO>(), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(yaml.as<qm::parsers::yaml::ApplicationYamlDTO>(), "'node' is required for Application");
}

TEST_CASE("parse application from invalid yaml - invalid arguments", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
binary: ping
node: !Ref node01
arguments: 127.0.0.1
stackSize: 1048576
)");

    REQUIRE_THROWS_AS(yaml.as<qm::parsers::yaml::ApplicationYamlDTO>(), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(yaml.as<qm::parsers::yaml::ApplicationYamlDTO>(), "'arguments' should be an array");
}
