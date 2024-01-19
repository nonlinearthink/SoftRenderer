#define CATCH_CONFIG_MAIN

#include "SoftRenderer/common.h"
#include "SoftRenderer/vec.h"
#include "catch2/catch_test_macros.hpp"

using namespace SoftRenderer;

TEST_CASE("Vector2 Tests") {  // NOLINT
    Vector2i v1(1, 2);
    Vector2i v2(3, 4);
    Vector2i v3(5, 6);

    SECTION("Operator[]") {
        REQUIRE(v1[0] == 1);
        REQUIRE(v1[1] == 2);
        REQUIRE(v2[0] == 3);
        REQUIRE(v2[1] == 4);
    }

    SECTION("Operator+") {
        Vector2<int> result = v1 + v2;
        REQUIRE(result.x == 4);
        REQUIRE(result.y == 6);
    }

    SECTION("Operator-") {
        Vector2<int> result = v1 - v2;
        REQUIRE(result.x == -2);
        REQUIRE(result.y == -2);
    }

    SECTION("Operator*") {
        Vector2<int> result = v1 * v2;
        REQUIRE(result.x == 3);
        REQUIRE(result.y == 8);
    }

    SECTION("Operator* with scalar") {
        Vector2<int> result = v1 * 3;
        REQUIRE(result.x == 3);
        REQUIRE(result.y == 6);
    }
}

TEST_CASE("Vector3 Tests", "[Vector3]") {  // NOLINT
    float epsilon = std::numeric_limits<float>::epsilon();

    Vector3f v1(1.f, 2.f, 3.f);
    Vector3f v2(4.f, 5.f, 6.f);

    SECTION("Operator[]") {
        REQUIRE(Equals(v1[0], 1.f));
        REQUIRE(Equals(v1[1], 2.f));
        REQUIRE(Equals(v1[2], 3.f));
    }

    SECTION("Operator+") {
        Vector3f v3 = v1 + v2;
        REQUIRE(Equals(v3.x, 5.f));
        REQUIRE(Equals(v3.y, 7.f));
        REQUIRE(Equals(v3.z, 9.f));
    }

    SECTION("Operator-") {
        Vector3f v3 = v1 - v2;
        REQUIRE(Equals(v3.x, -3.f));
        REQUIRE(Equals(v3.y, -3.f));
        REQUIRE(Equals(v3.z, -3.f));
    }

    SECTION("Operator*") {
        Vector3f v3 = v1 * v2;
        REQUIRE(Equals(v3.x, 4.f));
        REQUIRE(Equals(v3.y, 10.f));
        REQUIRE(Equals(v3.z, 18.f));
    }

    SECTION("Operator* with scalar") {
        Vector3f v3 = v1 * 2.f;
        REQUIRE(Equals(v3.x, 2.f));
        REQUIRE(Equals(v3.y, 4.f));
        REQUIRE(Equals(v3.z, 6.f));
    }

    SECTION("LengthSquare") {
        float lenSqr = v1.LengthSquare();
        REQUIRE(Equals(lenSqr, 14.f));
    }

    SECTION("Length") {
        float len = v1.Length();
        REQUIRE(Equals(len, std::sqrt(14.f)));
    }

    SECTION("Dot") {
        float result = v1.Dot(v2);
        REQUIRE(Equals(result, 32.f));
    }

    SECTION("Cross") {
        Vector3f result = v1.Cross(v2);
        REQUIRE(Equals(result.x, -3.f));
        REQUIRE(Equals(result.y, 6.f));
        REQUIRE(Equals(result.z, -3.f));
    }

    SECTION("Normalize") {
        Vector3f result = v1.Normalize();
        float len = result.Length();
        REQUIRE(Equals(len, 1.f));
        REQUIRE(Equals(result.x, 1.f / std::sqrt(14.f)));
        REQUIRE(Equals(result.y, 2.f / std::sqrt(14.f)));
        REQUIRE(Equals(result.z, 3.f / std::sqrt(14.f)));
    }
}
