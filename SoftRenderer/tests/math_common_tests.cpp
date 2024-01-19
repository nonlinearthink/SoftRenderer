#define CATCH_CONFIG_MAIN

#include "SoftRenderer/common.h"
#include "catch2/catch_test_macros.hpp"

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
