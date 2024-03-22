#define CATCH_CONFIG_MAIN

#include "SoftRenderer/common.h"
#include "catch2/catch_test_macros.hpp"

using namespace MathUtils;
using namespace StringUtils;

TEST_CASE("Degree To Radian") {  // NOLINT
    REQUIRE(Equals(DegreeToRadian(0), 0.f));
    REQUIRE(Equals(DegreeToRadian(90), C_PI() / 2));
    REQUIRE(Equals(DegreeToRadian(180), C_PI()));
    REQUIRE(Equals(DegreeToRadian(360), 2 * C_PI()));
}

TEST_CASE("Radian To Degree") {  // NOLINT
    REQUIRE(Equals(RadianToDegree(0), 0.f));
    REQUIRE(Equals(RadianToDegree(C_PI() / 4), 45.f));
    REQUIRE(Equals(RadianToDegree(C_PI() / 2), 90.f));
    REQUIRE(Equals(RadianToDegree(3 * C_PI() / 4), 135.f));
    REQUIRE(Equals(RadianToDegree(C_PI()), 180.f));
    REQUIRE(Equals(RadianToDegree(2 * C_PI()), 360.f));
}

TEST_CASE("A normal string endwiths",  // NOLINT
          "[StringUtil][Endwith]") {
    REQUIRE(EndsWith("Hello, World!", "World!"));
    REQUIRE_FALSE(EndsWith("Hello, World!", "World"));
    REQUIRE_FALSE(EndsWith("Hello, World!", "Hello"));
}

TEST_CASE("A empty string endwiths",  // NOLINT
          "[StringUtil][Endwith]") {
    REQUIRE(EndsWith("", ""));
    REQUIRE_FALSE(EndsWith("", "World"));
}

TEST_CASE("format a string", "[StringUtil][Format]") {  // NOLINT
    std::string name = "World";
    std::string formatted = Format("Hello, {}!", {name.c_str()});
    REQUIRE(formatted == "Hello, World!");
}
