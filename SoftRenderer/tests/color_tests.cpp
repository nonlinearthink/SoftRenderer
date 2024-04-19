#include "SoftRenderer/color.h"
#include "catch2/catch_test_macros.hpp"

#define CATCH_CONFIG_MAIN

using namespace SoftRenderer;

/// NOLINTBEGIN(cert-err58-cpp)
TEST_CASE("Adding two colors") {
    Color c1{0.1f, 0.2f, 0.3f, 0.4f};
    Color c2{0.5f, 0.6f, 0.7f, 0.8f};

    Color c3{c1 + c2};
    REQUIRE(c3 == Color{0.6f, 0.8f, 1.f, 1.f});
}

TEST_CASE("Subtracting two colors") {
    Color c1{0.6f, 0.2f, 0.3f, 0.4f};
    Color c2{0.5f, 0.6f, 0.7f, 0.8f};

    Color c3{c2 - c1};
    REQUIRE(c3 == Color{0.f, 0.4f, 0.4f, 0.4f});
}

TEST_CASE("Multiplying a color with a scaler") {
    Color c1{0.3f, 0.2f, 0.1f};

    Color c2{c1 * 3};
    REQUIRE(c2 == Color{0.9f, 0.6f, 0.3f, 1.f});
}

TEST_CASE("Dividing a color by a scaler") {
    Color c1{0.6f, 0.8f, 0.4f};

    Color c2{c1 / 2};
    REQUIRE(c2 == Color{0.3f, 0.4f, 0.2f, 0.5f});
}
/// NOLINTEND(cert-err58-cpp)