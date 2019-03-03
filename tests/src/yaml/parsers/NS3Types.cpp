#import <catch2/catch.hpp>
#import <yaml-cpp/yaml.h>
#import <qm/yaml/parsers/NS3Types.hpp>

// those test cases don't cover cases with invalid yaml,
// because ns3::Time constructor on invalid string doesn't throw an exception, but calls std::terminate

TEST_CASE("parse ns3::Time from valid yaml", "[parsers][yaml]") {
    std::map<std::string, ns3::Time::Unit> units = {
      {"s",   ns3::Time::Unit::S},
      {"ms",  ns3::Time::Unit::MS},
      {"us",  ns3::Time::Unit::US},
      {"ns",  ns3::Time::Unit::NS},
      {"ps",  ns3::Time::Unit::PS},
      {"min", ns3::Time::Unit::MIN},
      {"h",   ns3::Time::Unit::H},
      {"d",   ns3::Time::Unit::D},
      {"y",   ns3::Time::Unit::Y},
    };

    for (const auto&[unitStr, unitValue] : units) {
        for (auto i = 0.0; i < 2; i += 0.5) {
            const auto expected = ns3::Time::FromDouble(i, unitValue);
            const auto actual = YAML::Load(std::to_string(i) + unitStr).as<ns3::Time>();

            REQUIRE(expected == actual);
        }
    }
}

TEST_CASE("parse ns3::DataRate from valid yaml", "[parsers][yaml]") {
    const uint64_t kilo = 1000;
    const uint64_t kibi = 1024;

    std::map<std::string, uint64_t> units = {
      {"bps",   1},
      {"b/s",   1},
      {"Bps",   8},
      {"B/s",   8},
      {"kbps",  1 * kilo},
      {"kb/s",  1 * kilo},
      {"Kbps",  1 * kilo},
      {"Kb/s",  1 * kilo},
      {"kBps",  8 * kilo},
      {"kB/s",  8 * kilo},
      {"KBps",  8 * kilo},
      {"KB/s",  8 * kilo},
      {"Kib/s", 1 * kibi},
      {"KiB/s", 8 * kibi},
      {"Mbps",  1 * kilo * kilo},
      {"Mb/s",  1 * kilo * kilo},
      {"MBps",  8 * kilo * kilo},
      {"MB/s",  8 * kilo * kilo},
      {"Mib/s", 1 * kibi * kibi},
      {"MiB/s", 8 * kibi * kibi},
      {"Gbps",  1 * kilo * kilo * kilo},
      {"Gb/s",  1 * kilo * kilo * kilo},
      {"GBps",  8 * kilo * kilo * kilo},
      {"GB/s",  8 * kilo * kilo * kilo},
      {"Gib/s", 1 * kibi * kibi * kibi},
      {"GiB/s", 8 * kibi * kibi * kibi}
    };

    for (const auto&[unitStr, unitValue] : units) {
        for (auto i = 0; i < 1024; i += 128) {
            const auto input = std::to_string(i) + unitStr;
            const auto expected = i * unitValue;

            SECTION(std::to_string(i) + " " + std::to_string(unitValue) + " convert " + input + " to ns3::DataRate(" +
                    std::to_string(expected) + ") bits") {
                const auto actual = YAML::Load(input).as<ns3::DataRate>();

                REQUIRE(actual.GetBitRate() == expected);
            }
        }
    }
}
