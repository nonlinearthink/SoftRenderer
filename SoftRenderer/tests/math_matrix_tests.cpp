#define CATCH_CONFIG_MAIN

#include "SoftRenderer/math/matrix.h"
#include "catch2/catch_test_macros.hpp"

using namespace SoftRenderer;

TEST_CASE("Matrix base case", "[Matrix]") {
    Matrix m1{}, m2{};

    SECTION("Matrix addition") {
        Matrix result = (m1 + m2) / 2.f;

        Matrix compare;

        REQUIRE_FALSE(!(compare == result));
    }
}
