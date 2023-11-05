#include "catch2/catch_test_macros.hpp"
#include "utils.h"

TEST_CASE("degree_to_radian") {
    REQUIRE(std::abs(utils::degree_to_radian(0) - 0) < 1e-6);
    REQUIRE(std::abs(utils::degree_to_radian(90) - utils::M_PI / 2) < 1e-6);
    REQUIRE(std::abs(utils::degree_to_radian(180) - utils::M_PI) < 1e-6);
    REQUIRE(std::abs(utils::degree_to_radian(360) - 2 * utils::M_PI) < 1e-6);
}

TEST_CASE("radian_to_degree") {
    REQUIRE(std::abs(utils::radian_to_degree(0) - 0) < 1e-6);
    REQUIRE(std::abs(utils::radian_to_degree(utils::M_PI / 4) - 45) < 1e-6);
    REQUIRE(std::abs(utils::radian_to_degree(utils::M_PI / 2) - 90) < 1e-6);
    REQUIRE(std::abs(utils::radian_to_degree(3 * utils::M_PI / 4) - 135) <
            1e-6);
    REQUIRE(std::abs(utils::radian_to_degree(utils::M_PI) - 180) < 1e-6);
    REQUIRE(std::abs(utils::radian_to_degree(2 * utils::M_PI) - 360) < 1e-6);
}
