#include <catch2/catch.hpp>
#include <qm/services/utils/FileModeBuilder.hpp>

using FMBuilder = qm::services::utils::FileModeBuilder;

TEST_CASE("zero by default", "[fs][system]") {
    REQUIRE(FMBuilder{}.Build() == 0);
}


TEST_CASE("clear set zero", "[fs][system]") {
    REQUIRE(FMBuilder{}.GrantAllToAll().Clear().Build() == 0);
}

TEST_CASE("Grant to All", "[fs][system]") {
    SECTION("GrantAllToAll") {
        REQUIRE(FMBuilder{}.GrantAllToAll().Build() == 0777);
    }

    SECTION("GrantReadToAll") {
        REQUIRE(FMBuilder{}.GrantReadToAll().Build() == 0444);
    }

    SECTION("GrantWriteToAll") {
        REQUIRE(FMBuilder{}.GrantWriteToAll().Build() == 0222);
    }

    SECTION("GrantExecuteToAll") {
        REQUIRE(FMBuilder{}.GrantExecuteToAll().Build() == 0111);
    }

    SECTION("GrantSearchToAll == GrantExecuteToAll") {
        REQUIRE(FMBuilder{}.GrantExecuteToAll().Build() == FMBuilder{}.GrantExecuteToAll().Build());
    }
}

TEST_CASE("Grant to Owner", "[fs][system]") {
    SECTION("GrantAllToOwner") {
        REQUIRE(FMBuilder{}.GrantAllToOwner().Build() == 0700);
    }

    SECTION("GrantReadToOwner") {
        REQUIRE(FMBuilder{}.GrantReadToOwner().Build() == 0400);
    }

    SECTION("GrantWriteToOwner") {
        REQUIRE(FMBuilder{}.GrantWriteToOwner().Build() == 0200);
    }

    SECTION("GrantExecuteToOwner") {
        REQUIRE(FMBuilder{}.GrantExecuteToOwner().Build() == 0100);
    }

    SECTION("GrantSearchToOwner == GrantExecuteToOwner") {
        REQUIRE(FMBuilder{}.GrantExecuteToOwner().Build() == FMBuilder{}.GrantExecuteToOwner().Build());
    }
}

TEST_CASE("Grant to Group", "[fs][system]") {
    SECTION("GrantAllToGroup") {
        REQUIRE(FMBuilder{}.GrantAllToGroup().Build() == 0070);
    }

    SECTION("GrantReadToGroup") {
        REQUIRE(FMBuilder{}.GrantReadToGroup().Build() == 0040);
    }

    SECTION("GrantWriteToGroup") {
        REQUIRE(FMBuilder{}.GrantWriteToGroup().Build() == 0020);
    }

    SECTION("GrantExecuteToGroup") {
        REQUIRE(FMBuilder{}.GrantExecuteToGroup().Build() == 0010);
    }

    SECTION("GrantSearchToGroup == GrantExecuteToGroup") {
        REQUIRE(FMBuilder{}.GrantExecuteToGroup().Build() == FMBuilder{}.GrantExecuteToGroup().Build());
    }
}

TEST_CASE("Grant to Others", "[fs][system]") {
    SECTION("GrantAllToOthers") {
        REQUIRE(FMBuilder{}.GrantAllToOthers().Build() == 0007);
    }

    SECTION("GrantReadToOthers") {
        REQUIRE(FMBuilder{}.GrantReadToOthers().Build() == 0004);
    }

    SECTION("GrantWriteToOthers") {
        REQUIRE(FMBuilder{}.GrantWriteToOthers().Build() == 0002);
    }

    SECTION("GrantExecuteToOthers") {
        REQUIRE(FMBuilder{}.GrantExecuteToOthers().Build() == 0001);
    }

    SECTION("GrantSearchToOthers == GrantExecuteToOthers") {
        REQUIRE(FMBuilder{}.GrantExecuteToOthers().Build() == FMBuilder{}.GrantExecuteToOthers().Build());
    }
}

TEST_CASE("Grant special", "[fs][system]") {
    SECTION("Set SUID bit") {
        REQUIRE(FMBuilder{}.SetSUID().Build() == 04000);
    }

    SECTION("Set SGID bit") {
        REQUIRE(FMBuilder{}.SetSGID().Build() == 02000);
    }

    SECTION("Set Sticky bit") {
        REQUIRE(FMBuilder{}.SetRestrictedDeletionFlag().Build() == 01000);
    }
}

TEST_CASE("Grant mixed", "[fs][system]") {
    SECTION("0744") {
        REQUIRE(FMBuilder{}.GrantAllToOwner().GrantReadToGroup().GrantReadToOthers().Build() == 0744);
    }

    SECTION("0760") {
        REQUIRE(FMBuilder{}.GrantAllToOwner().GrantReadToGroup().GrantWriteToGroup().Build() == 0760);
    }

    SECTION("0655") {
        REQUIRE(
          FMBuilder{}
            .GrantReadToOwner()
            .GrantWriteToOwner()
            .GrantReadToGroup()
            .GrantExecuteToGroup()
            .GrantReadToOthers()
            .GrantExecuteToOthers()
            .Build() == 0655);
    }
}
