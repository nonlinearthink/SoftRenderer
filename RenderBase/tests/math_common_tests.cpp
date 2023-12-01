#include "catch2/catch_test_macros.hpp"
#include "renderbase/math/common.h"

using namespace RenderBase;

TEST_CASE("Degree To Radian") {
    float epsilon = std::numeric_limits<float>::epsilon();

    REQUIRE(std::abs(DegreeToRadian(0) - 0) <= epsilon);
    REQUIRE(std::abs(DegreeToRadian(90) - RenderBase::PI / 2) <= epsilon);
    REQUIRE(std::abs(DegreeToRadian(180) - RenderBase::PI) <= epsilon);
    REQUIRE(std::abs(DegreeToRadian(360) - 2 * RenderBase::PI) <= epsilon);
}

TEST_CASE("Radian To Degree") {
    float epsilon = std::numeric_limits<float>::epsilon();

    REQUIRE(std::abs(RadianToDegree(0) - 0) < epsilon);
    REQUIRE(std::abs(RadianToDegree(RenderBase::PI / 4) - 45) <= epsilon);
    REQUIRE(std::abs(RadianToDegree(RenderBase::PI / 2) - 90) <= epsilon);
    REQUIRE(std::abs(RadianToDegree(3 * RenderBase::PI / 4) - 135) <=
            epsilon);
    REQUIRE(std::abs(RadianToDegree(RenderBase::PI) - 180) <= epsilon);
    REQUIRE(std::abs(RadianToDegree(2 * RenderBase::PI) - 360) <= epsilon);
}
