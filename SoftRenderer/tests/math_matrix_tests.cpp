#define CATCH_CONFIG_MAIN

#include "SoftRenderer/math/matrix.h"
#include "catch2/catch_test_macros.hpp"

using namespace SoftRenderer;

TEST_CASE("Matrix Tests", "[Matrix]") {
    Matrix m0, m1 = Matrix::Identity(), m2{};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m2.m[i][j] = i * 4 + j;
        }
    }

    SECTION("Identity") {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(m1.m[i][j] == 1);
                } else {
                    REQUIRE(m1.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Addition") {
        Matrix result = m0 + Matrix::Identity();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(result.m[i][j] == 1);
                } else {
                    REQUIRE(result.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Subtraction") {
        Matrix result = m0 - m1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(result.m[i][j] == -1);
                } else {
                    REQUIRE(result.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Multiplication") {
        Matrix result = m2 * Matrix::Identity();
        // Add your own checks
    }

    SECTION("Scalar multiplication") {
        Matrix result = m1 * 2.0f;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(result.m[i][j] == 2);
                } else {
                    REQUIRE(result.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Scalar division") {
        Matrix result = m1 / 2.0f;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(result.m[i][j] == 0.5);
                } else {
                    REQUIRE(result.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Transpose") {
        Matrix result = m0.Transpose();
        // Add your own checks
    }

    SECTION("Vector multiplication") {
        Vector3f v;
        v = m0.MultiplyVector(v);
        // Add your own checks
    }
}
