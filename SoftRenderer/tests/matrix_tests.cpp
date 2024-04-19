#include "SoftRenderer/matrix.h"
#include "catch2/catch_test_macros.hpp"

#define CATCH_CONFIG_MAIN

using namespace SoftRenderer;

/// NOLINTBEGIN(cert-err58-cpp)
TEST_CASE("Matrix Tests", "[Matrix]") {
    Matrix2 mat2{1, 2, 3, 4};
    Matrix3 mat3{1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix4 mat4i{Matrix4::Identity()},
        mat4{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    SECTION("Identity") {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(mat4i.m[i][j] == 1);
                } else {
                    REQUIRE(mat4i.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Addition") {
        Matrix4 result = mat4i + mat4;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(result.m[i][j] == 2 + i * 4 + j);
                } else {
                    REQUIRE(result.m[i][j] == 1 + i * 4 + j);
                }
            }
        }
    }

    SECTION("Subtraction") {
        Matrix4 result = mat4i - mat4;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(result.m[i][j] == -i * 4 - j);
                } else {
                    REQUIRE(result.m[i][j] == -1 - i * 4 - j);
                }
            }
        }
    }

    SECTION("Multiplication") {
        Matrix4 result = mat4i * mat4;
        REQUIRE(result == mat4);
    }

    SECTION("Scalar multiplication") {
        Matrix4 result = mat4i * 2.f;
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
        Matrix4 result = mat4i / 2.f;
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
        Matrix4 result = mat4.Transpose();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                REQUIRE(result.m[i][j] == mat4.m[j][i]);
            }
        }
    }

    SECTION("Determinant") {
        REQUIRE(mat2.Determinant() == -2);
        REQUIRE(mat3.Determinant() == 0);
        REQUIRE(mat4.Determinant() == 0);
    }

    SECTION("Inverse") {
        Matrix2 mat2inverse = mat2.Invert();
        Matrix2 mat2check{-2, 1, 1.5, -0.5};
        REQUIRE(mat2inverse == mat2check);

        Matrix3 mat3inverse = mat3.Invert();
        REQUIRE(mat3inverse == mat3);

        Matrix4 mat4inverse = mat4.Invert();
        REQUIRE(mat4inverse == mat4);
    }
}
/// NOLINTEND(cert-err58-cpp)
