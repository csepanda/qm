#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

// TODO update tests
TEST_CASE("File parsing. Valid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
path: /etc/foo/bar.cfg
text: |
  debug=true
  logLevel=verbose
)");

    const auto actual = yaml.as<qm::yaml::dto::File>();

    SECTION("correct implicitly parsed type is set") {
        REQUIRE(actual.Type == qm::models::FileType::Regular);
    }

    SECTION("source of regular file is correctly determined by parser") {
        REQUIRE(actual.RegularSourceType == qm::yaml::dto::RegularFileSourceType::Text);
    }

    SECTION("path is parsed correctly") {
        REQUIRE(actual.Path == "/etc/foo/bar.cfg");
    }

    SECTION("Multiline text content is parsed correctly") {
        REQUIRE(actual.TextContent == "debug=true\nlogLevel=verbose\n");
    }
}

TEST_CASE("File parsing. Invalid Yaml") {
    SECTION("Path is missing") {
        const YAML::Node yaml = YAML::Load(R"(
text: |
  debug=true
  logLevel=verbose
)");

        REQUIRE_THROWS(yaml.as<qm::yaml::dto::File>());
    }
}

