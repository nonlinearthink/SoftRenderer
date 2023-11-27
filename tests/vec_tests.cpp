#include "catch2/catch_test_macros.hpp"
#include "core/vec.h"

class Vector2TestFixture {
   protected:
    Vector2<int> v1;
    Vector2<int> v2;

   public:
    Vector2TestFixture() : v1(1, 2), v2(3, 4) {}
};

TEST_CASE_METHOD(Vector2TestFixture, "Vector2 addition", "[Vector2]") {
    Vector2<int> result = v1 + v2;
    REQUIRE(result.x == 4);
    REQUIRE(result.y == 6);
}

TEST_CASE_METHOD(Vector2TestFixture, "Vector2 subtraction", "[Vector2]") {
    SECTION("Subtracting v2 from v1") {
        Vector2<int> result = v1 - v2;
        REQUIRE(result.x == -2);
        REQUIRE(result.y == -2);
    }

    SECTION("Subtracting v1 from v2") {
        Vector2<int> result = v2 - v1;
        REQUIRE(result.x == 2);
        REQUIRE(result.y == 2);
    }
}