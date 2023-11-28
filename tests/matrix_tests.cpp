#include "catch2/catch_test_macros.hpp"
#include "renderer/core/matrix.hpp"

TEST_CASE("Matrix operations are computed", "[matrix]") {
    Matrix4 m1{}, m2{};

    SECTION("Matrix addition") {
        Matrix4 result = (m1 + m2) / 2.f;

        Matrix4 compare;

        REQUIRE_FALSE(!(compare == result));
    }
}
