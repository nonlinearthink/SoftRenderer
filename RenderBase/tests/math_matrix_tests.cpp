#include "catch2/catch_test_macros.hpp"
#include "renderbase/math/matrix.hpp"

using namespace RenderBase;

TEST_CASE("Matrix base case", "[Matrix]") {
    Matrix4 m1{}, m2{};

    SECTION("Matrix addition") {
        Matrix4 result = (m1 + m2) / 2.f;

        Matrix4 compare;

        REQUIRE_FALSE(!(compare == result));
    }
}
