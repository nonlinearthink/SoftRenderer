#define CATCH_CONFIG_MAIN

#include "SoftRenderer/common.h"
#include "catch2/catch_test_macros.hpp"

using namespace MathUtils;
using namespace StringUtils;

// NOLINTBEGIN(cert-err58-cpp)
TEST_CASE("Degree To Radian") {
    REQUIRE(Equals(DegreeToRadian(0), 0.f));
    REQUIRE(Equals(DegreeToRadian(90), C_PI() / 2));
    REQUIRE(Equals(DegreeToRadian(180), C_PI()));
    REQUIRE(Equals(DegreeToRadian(360), 2 * C_PI()));
}

TEST_CASE("Radian To Degree") {
    REQUIRE(Equals(RadianToDegree(0), 0.f));
    REQUIRE(Equals(RadianToDegree(C_PI() / 4), 45.f));
    REQUIRE(Equals(RadianToDegree(C_PI() / 2), 90.f));
    REQUIRE(Equals(RadianToDegree(3 * C_PI() / 4), 135.f));
    REQUIRE(Equals(RadianToDegree(C_PI()), 180.f));
    REQUIRE(Equals(RadianToDegree(2 * C_PI()), 360.f));
}

SCENARIO("use EndsWith with a simple string") {
    GIVEN("a string 'Hello, World!'") {
        std::string test_string = "Hello, World!";

        THEN("it ends with 'World!'") {
            REQUIRE(EndsWith(test_string, "World!"));
        }
        THEN("it doesn't end with 'Hello'") {
            REQUIRE_FALSE(EndsWith(test_string, "Hello"));
        }
    }
}

SCENARIO("use EndsWith with a empty string") {
    GIVEN("a empty string") {
        std::string test_string;

        THEN("it ends with nothing") { REQUIRE(EndsWith(test_string, "")); }
        THEN("it doesn't end with 'Hello'") {
            REQUIRE_FALSE(EndsWith(test_string, "Hello"));
        }
    }
}

SCENARIO("format a string with one slot") {
    GIVEN("A format string 'Hello, {}!' and a insert string 'World'") {
        std::string fmt_str = "Hello, {}!";
        std::string str0 = "World";

        THEN("get a string 'Hello, World!'") {
            REQUIRE(Format(fmt_str, {str0.c_str()}) == "Hello, World!");
        }
    }
}

SCENARIO("format a string with multiple slot") {
    GIVEN(
        "a format string 'H{}, W{}!' and two insert string 'ello' and 'orld'") {
        std::string fmt_str = "H{}, W{}!";
        std::string str0 = "ello";
        std::string str1 = "orld";

        THEN("get a string 'Hello, World!'") {
            REQUIRE(Format(fmt_str, {str0.c_str(), str1.c_str()}) ==
                    "Hello, World!");
        }
    }
}
// NOLINTEND(cert-err58-cpp)
