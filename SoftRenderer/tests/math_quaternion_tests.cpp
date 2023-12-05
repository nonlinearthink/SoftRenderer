#define CATCH_CONFIG_MAIN

#include "SoftRenderer.h"
#include "catch2/catch_test_macros.hpp"

using namespace SoftRenderer;

TEST_CASE("Quaternion base case", "[Quaternion]") {
    Quaternion q1(1, 2, 3, 4);
    Quaternion q2(5, 6, 7, 8);

    SECTION("Quaternion Multiplication") {
        Quaternion q3 = q1 * q2;
        REQUIRE(Equals(q3.x, 24));
        REQUIRE(Equals(q3.y, 48));
        REQUIRE(Equals(q3.z, 48));
        REQUIRE(Equals(q3.w, -6));
    }

    SECTION("Quaternion Conjugate") {
        Quaternion q4 = q1.Conjugate();
        REQUIRE(Equals(q4.x, -1));
        REQUIRE(Equals(q4.y, -2));
        REQUIRE(Equals(q4.z, -3));
        REQUIRE(Equals(q4.w, 4));
    }

    SECTION("Quaternion normalize") {
        Quaternion q5 = q1.Normalize();
        REQUIRE(
            Equals(q5.x * q5.x + q5.y * q5.y + q5.z * q5.z + q5.w * q5.w, 1));
    }
}
