#include <sstream>

#include "SoftRenderer/common.h"
#include "SoftRenderer/vec.h"
#include "catch2/catch_test_macros.hpp"

#define CATCH_CONFIG_MAIN

using namespace SoftRenderer;
using namespace MathUtils;

/// NOLINTBEGIN(cert-err58-cpp)
SCENARIO("Vector2i test scenario") {
    GIVEN("A default Vector2i instance") {
        Vector2i v1;

        THEN("The x and y components should be initialized to zero") {
            REQUIRE(v1.x == 0);
            REQUIRE(v1.y == 0);
        }
    }

    GIVEN("A Vector2i instance") {
        Vector2i v1{-1, 2};

        THEN("The x and y components should match their initialization") {
            REQUIRE(v1.x == -1);
            REQUIRE(v1.y == 2);
        }

        THEN(
            "The array index should be able to access the x and y components") {
            REQUIRE(v1[0] == v1.x);
            REQUIRE(v1[1] == v1.y);
        }

        WHEN("Copying the vector by an new vector") {
            Vector2i v2{v1};

            THEN("The copied vector should have identical x and y components") {
                REQUIRE(v1.x == v2.x);
                REQUIRE(v1.y == v2.y);
            }
        }

        WHEN("Multiplying the vector by an integer scalar") {
            auto result = v1 * 3;

            THEN("The result vector should have triple x and y components") {
                REQUIRE(result.x == -3);
                REQUIRE(result.y == 6);
            }
        }

        WHEN("Serializing Vector2") {
            std::ostringstream oss;
            oss << v1;

            THEN("Matching the specific result") {
                REQUIRE(oss.str() == "Vector2<int>(-1, 2)");
            }
        }

        GIVEN(
            "A default vector and applying CopyFrom with the existing vector") {
            Vector2i v2;
            v2.CopyFrom(v1);

            THEN(
                "The x and y components should be same with the existing "
                "vector") {
                REQUIRE(v2.x == v1.x);
                REQUIRE(v2.y == v1.y);
            }
        }
    }

    GIVEN("Two Vector2i instance") {
        Vector2i v1{-1, -1};
        Vector2i v2{2, 3};

        WHEN("Adding the two vectors") {
            auto result = v1 + v2;

            THEN("The result vector should have summed x and y components") {
                REQUIRE(result.x == 1);
                REQUIRE(result.y == 2);
            }
        }

        WHEN("Subtracting the two vectors") {
            auto result = v1 - v2;

            THEN(
                "The result vector should have subtracted x and y components") {
                REQUIRE(result.x == -3);
                REQUIRE(result.y == -4);
            }
        }

        WHEN("Multiplying the two vector") {
            auto result = v1 * v2;

            THEN(
                "The result vector should have element-wise multiplied x and y "
                "components") {
                REQUIRE(result.x == -2);
                REQUIRE(result.y == -3);
            }
        }
    }
}

SCENARIO("Vector3f test scenario") {
    float epsilon = std::numeric_limits<float>::epsilon();

    GIVEN("A default Vector3f instance") {
        Vector3f v1;

        THEN("The x, y and z components should be initialized to zero") {
            REQUIRE(Equals(v1.x, 0.f));
            REQUIRE(Equals(v1.y, 0.f));
            REQUIRE(Equals(v1.z, 0.f));
        }
    }

    GIVEN("A Vector3f instance") {
        Vector3f v1{-1.f, 2.f, -3.f};

        THEN("The x, y and z components should match their initialization") {
            REQUIRE(Equals(v1.x, -1.f));
            REQUIRE(Equals(v1.y, 2.f));
            REQUIRE(Equals(v1.z, -3.f));
        }

        THEN(
            "The array index should be able to access the x, y and z "
            "components") {
            REQUIRE(Equals(v1[0], v1.x));
            REQUIRE(Equals(v1[1], v1.y));
            REQUIRE(Equals(v1[2], v1.z));
        }

        GIVEN("A copy of the vector") {
            Vector3f v2{v1};

            THEN(
                "The copied vector should have identical x, y and z "
                "components") {
                REQUIRE(Equals(v1.x, v2.x));
                REQUIRE(Equals(v1.y, v2.y));
                REQUIRE(Equals(v1.z, v2.z));
            }
        }

        WHEN("Multiplying the vector by an integer scalar") {
            auto result = v1 * 3;

            THEN("The result vector should have triple x, y and z components") {
                REQUIRE(Equals(result.x, -3.f));
                REQUIRE(Equals(result.y, 6.f));
                REQUIRE(Equals(result.z, -9.f));
            }
        }

        WHEN("Serializing Vector3") {
            std::ostringstream oss;
            oss << v1;

            THEN("Matching the specific result") {
                REQUIRE(oss.str() == "Vector3<float>(-1, 2, -3)");
            }
        }

        GIVEN(
            "A default vector and applying CopyFrom with the existing vector") {
            Vector3f v2;
            v2.CopyFrom(v1);

            THEN(
                "The x, y and z components should be same with the existing "
                "vector") {
                REQUIRE(Equals(v1.x, v2.x));
                REQUIRE(Equals(v1.y, v2.y));
                REQUIRE(Equals(v1.z, v2.z));
            }
        }

        THEN("") {
            float len_s = v1.LengthSquare();
            REQUIRE(Equals(len_s, 14.f));
        }

        THEN("") {
            float len = v1.Length();
            REQUIRE(Equals(len, std::sqrt(14.f)));
        }

        THEN("") {
            Vector3f result = v1.Normalize();

            float len = result.Length();
            REQUIRE(Equals(len, 1.f));
            REQUIRE(Equals(result.x, -1.f / std::sqrt(14.f)));
            REQUIRE(Equals(result.y, 2.f / std::sqrt(14.f)));
            REQUIRE(Equals(result.z, -3.f / std::sqrt(14.f)));
        }
    }

    GIVEN("Two Vector3f instance") {
        Vector3f v1{1.f, 2.f, 3.f};
        Vector3f v2{4.f, 5.f, 6.f};

        WHEN("Adding the two vectors") {
            auto v3 = v1 + v2;

            THEN("The result vector should have summed x and y components") {
                REQUIRE(Equals(v3.x, 5.f));
                REQUIRE(Equals(v3.y, 7.f));
                REQUIRE(Equals(v3.z, 9.f));
            }
        }

        WHEN("Subtracting the two vectors") {
            auto v3 = v1 - v2;

            THEN(
                "The result vector should have subtracted x and y components") {
                REQUIRE(Equals(v3.x, -3.f));
                REQUIRE(Equals(v3.y, -3.f));
                REQUIRE(Equals(v3.z, -3.f));
            }
        }

        WHEN("Multiplying the two vectors") {
            auto v3 = v1 * v2;

            THEN(
                "The result vector should have element-wise multiplied x, y "
                "and z components") {
                REQUIRE(Equals(v3.x, 4.f));
                REQUIRE(Equals(v3.y, 10.f));
                REQUIRE(Equals(v3.z, 18.f));
            }
        }

        WHEN("Dot product of the two vectors") {
            float result = v1.Dot(v2);

            THEN("Get the expected result") { REQUIRE(Equals(result, 32.f)); }
        }

        WHEN("Cross product of the two vectors") {
            Vector3f result = v1.Cross(v2);

            THEN("Get the expected result") {
                REQUIRE(Equals(result.x, -3.f));
                REQUIRE(Equals(result.y, 6.f));
                REQUIRE(Equals(result.z, -3.f));
            }
        }
    }
}
/// NOLINTEND(cert-err58-cpp)
