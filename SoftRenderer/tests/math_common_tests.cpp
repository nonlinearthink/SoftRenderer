#define CATCH_CONFIG_MAIN

#include "SoftRenderer/math/common.h"
#include "catch2/catch_test_macros.hpp"

using namespace SoftRenderer;

TEST_CASE("Degree To Radian") {
    REQUIRE(Equals(DegreeToRadian(0), 0));
    REQUIRE(Equals(DegreeToRadian(90), pi() / 2));
    REQUIRE(Equals(DegreeToRadian(180), pi()));
    REQUIRE(Equals(DegreeToRadian(360), 2 * pi()));
}

TEST_CASE("Radian To Degree") {
    REQUIRE(Equals(RadianToDegree(0), 0));
    REQUIRE(Equals(RadianToDegree(pi() / 4), 45));
    REQUIRE(Equals(RadianToDegree(pi() / 2), 90));
    REQUIRE(Equals(RadianToDegree(3 * pi() / 4), 135));
    REQUIRE(Equals(RadianToDegree(pi()), 180));
    REQUIRE(Equals(RadianToDegree(2 * pi()), 360));
}
