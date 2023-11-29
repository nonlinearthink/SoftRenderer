#include "catch2/catch_test_macros.hpp"
#include "renderlib/utils.h"

using namespace Renderlib;

TEST_CASE("degree_to_radian") {
    REQUIRE(std::abs(degree_to_radian(0) - 0) < 1e-6);
    REQUIRE(std::abs(degree_to_radian(90) - M_PI / 2) < 1e-6);
    REQUIRE(std::abs(degree_to_radian(180) - M_PI) < 1e-6);
    REQUIRE(std::abs(degree_to_radian(360) - 2 * M_PI) < 1e-6);
}

TEST_CASE("radian_to_degree") {
    REQUIRE(std::abs(radian_to_degree(0) - 0) < 1e-6);
    REQUIRE(std::abs(radian_to_degree(M_PI / 4) - 45) < 1e-6);
    REQUIRE(std::abs(radian_to_degree(M_PI / 2) - 90) < 1e-6);
    REQUIRE(std::abs(radian_to_degree(3 * M_PI / 4) - 135) < 1e-6);
    REQUIRE(std::abs(radian_to_degree(M_PI) - 180) < 1e-6);
    REQUIRE(std::abs(radian_to_degree(2 * M_PI) - 360) < 1e-6);
}
