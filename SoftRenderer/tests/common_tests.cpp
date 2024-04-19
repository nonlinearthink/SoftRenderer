#include "SoftRenderer/common.h"
#include "catch2/catch_test_macros.hpp"

#define CATCH_CONFIG_MAIN

using namespace MathUtils;
using namespace StringUtils;

/// NOLINTBEGIN(cert-err58-cpp)
TEST_CASE("DegreeToRadian") {
    REQUIRE(Equals(DegreeToRadian(0), 0.f));
    REQUIRE(Equals(DegreeToRadian(90), C_PI() / 2));
    REQUIRE(Equals(DegreeToRadian(180), C_PI()));
    REQUIRE(Equals(DegreeToRadian(360), 2 * C_PI()));
}

TEST_CASE("RadianToDegree") {
    REQUIRE(Equals(RadianToDegree(0), 0.f));
    REQUIRE(Equals(RadianToDegree(C_PI() / 4), 45.f));
    REQUIRE(Equals(RadianToDegree(C_PI() / 2), 90.f));
    REQUIRE(Equals(RadianToDegree(3 * C_PI() / 4), 135.f));
    REQUIRE(Equals(RadianToDegree(C_PI()), 180.f));
    REQUIRE(Equals(RadianToDegree(2 * C_PI()), 360.f));
}

TEST_CASE("Equals") {
    SECTION("Float") {
        REQUIRE(Equals(0.f, 0.f));
        REQUIRE(!Equals(0.f, 0.0001f));
        REQUIRE(Equals(0.f, 0.0000001f));
    }

    SECTION("Double") {
        REQUIRE(Equals(0., 0.));
        REQUIRE(!Equals(0., 0.0001));
        REQUIRE(!Equals(0., 0.0000001));
        REQUIRE(Equals(0., 0.0000000000000001));
    }
}

TEST_CASE("EndsWith") {
    SECTION("A normal string") {
        std::string test_string = "Hello, World!";
        REQUIRE(EndsWith(test_string, "World!"));
        REQUIRE_FALSE(EndsWith(test_string, "Hello"));
    }

    SECTION("A empty string") {
        std::string test_string;
        REQUIRE(EndsWith(test_string, ""));
        REQUIRE_FALSE(EndsWith(test_string, "Hello"));
    }
}

TEST_CASE("Format") {
    SECTION("One Slot") {
        std::string fmt_str = "Hello, {}!";
        std::string str0 = "World";
        REQUIRE(Format(fmt_str, {str0.c_str()}) == "Hello, World!");
    }

    SECTION("Two Slot") {
        std::string fmt_str = "H{}, W{}!";
        std::string str0 = "ello";
        std::string str1 = "orld";
        REQUIRE(Format(fmt_str, {str0.c_str(), str1.c_str()}) ==
                "Hello, World!");
    }
}
/// NOLINTEND(cert-err58-cpp)
