#include "catch2/catch_test_macros.hpp"
#include "renderbase/math/quaternion.h"

using namespace RenderBase;

TEST_CASE("Quaternion base case", "[Quaternion]") {
    Quaternion q1(1, 2, 3, 4);
    Quaternion q2(5, 6, 7, 8);

    float epsilon = std::numeric_limits<float>::epsilon();

    SECTION("Quaternion Multiplication") {
        Quaternion q3 = q1 * q2;
        REQUIRE(std::abs(q3.x - 24) <= epsilon);
        REQUIRE(std::abs(q3.y - 48) <= epsilon);
        REQUIRE(std::abs(q3.z - 48) <= epsilon);
        REQUIRE(std::abs(q3.w + 6) <= epsilon);
    }

    SECTION("Quaternion Conjugate") {
        Quaternion q4 = q1.conjugate();
        REQUIRE(std::abs(q4.x + 1) <= epsilon);
        REQUIRE(std::abs(q4.y + 2) <= epsilon);
        REQUIRE(std::abs(q4.z + 3) <= epsilon);
        REQUIRE(std::abs(q4.w - 4) <= epsilon);
    }

    SECTION("Quaternion normalize") {
        Quaternion q5 = q1.normalize();
        REQUIRE(std::abs(q5.x * q5.x + q5.y * q5.y + q5.z * q5.z + q5.w * q5.w -
                         1) <= epsilon);
    }
}
