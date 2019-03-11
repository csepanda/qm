#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

// TODO update tests
TEST_CASE("parse file from valid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
path: /etc/foo/bar.cfg
text: |
  debug=true
  logLevel=verbose
)");

    const auto actual = yaml.as<qm::yaml::dto::File>();

    REQUIRE(actual.Type == qm::models::FileType::Regular);
    REQUIRE(actual.RegularSourceType == qm::yaml::dto::RegularFileSourceType::Text);
    REQUIRE(actual.Path == "/etc/foo/bar.cfg");
    REQUIRE(actual.TextContent == "debug=true\nlogLevel=verbose\n");
}

