#define CATCH_CONFIG_MAIN

#include "SoftRenderer/common.h"
#include "SoftRenderer/quaternion.h"
#include "catch2/catch_test_macros.hpp"

using namespace SoftRenderer;
using namespace MathUtils;

TEST_CASE("Quaternion base case", "[Quaternion]") {  // NOLINT
    Quaternion q1(1, 2, 3, 4);
    Quaternion q2(5, 6, 7, 8);

    SECTION("Quaternion Multiplication") {
        Quaternion q3 = q1 * q2;
        REQUIRE(Equals(q3.x, 24.f));
        REQUIRE(Equals(q3.y, 48.f));
        REQUIRE(Equals(q3.z, 48.f));
        REQUIRE(Equals(q3.w, -6.f));
    }

    SECTION("Quaternion Conjugate") {
        Quaternion q4 = q1.Conjugate();
        REQUIRE(Equals(q4.x, -1.f));
        REQUIRE(Equals(q4.y, -2.f));
        REQUIRE(Equals(q4.z, -3.f));
        REQUIRE(Equals(q4.w, 4.f));
    }

    SECTION("Quaternion normalize") {
        Quaternion q5 = q1.Normalize();
        REQUIRE(
            Equals(q5.x * q5.x + q5.y * q5.y + q5.z * q5.z + q5.w * q5.w, 1.f));
    }
}
