#include "catch2/catch_test_macros.hpp"
#include "renderer/core/vec.hpp"

class Vector2TestFixture {
   protected:
    Vector2i v1;
    Vector2i v2;

   public:
    Vector2TestFixture() : v1(1, 2), v2(3, 4) {}
};

TEST_CASE_METHOD(Vector2TestFixture, "Vector2 addition", "[Vector2]") {
    Vector2i result = v1 + v2;
    REQUIRE(result.x == 4);
    REQUIRE(result.y == 6);
}

TEST_CASE_METHOD(Vector2TestFixture, "Vector2 subtraction", "[Vector2]") {
    Vector2i result = v1 - v2;
    REQUIRE(result.x == -2);
    REQUIRE(result.y == -2);
}

TEST_CASE_METHOD(Vector2TestFixture, "Vector2 multiplication", "[Vector2]") {
    Vector2i result = v1 * v2;
    REQUIRE(result.x == 3);
    REQUIRE(result.y == 8);
}

class Vector3TestFixture {
   protected:
    Vector3f v1;
    Vector3f v2;

   public:
    Vector3TestFixture() : v1(1., 2., 3.), v2(4., 5., 6.) {}
};

TEST_CASE_METHOD(Vector3TestFixture, "Vector3 addition", "[Vector3]") {
    Vector3f result = v1 + v2;
    REQUIRE(result.x == 5.);
    REQUIRE(result.y == 7.);
    REQUIRE(result.z == 9.);
}

TEST_CASE_METHOD(Vector3TestFixture, "Vector3 subtraction", "[Vector3]") {
    Vector3f result = v1 - v2;
    REQUIRE(result.x == -3.);
    REQUIRE(result.y == -3.);
    REQUIRE(result.z == -3.);
}

TEST_CASE_METHOD(Vector3TestFixture, "Vector3 multiplication", "[Vector3]") {
    Vector3f result = v1 * v2;
    REQUIRE(result.x == 4.);
    REQUIRE(result.y == 10.);
    REQUIRE(result.z == 18.);
}
