#define CATCH_CONFIG_MAIN

#include "SoftRenderer/math/matrix.hpp"
#include "catch2/catch_test_macros.hpp"

using namespace SoftRenderer;

TEST_CASE("Matrix Tests", "[Matrix]") {
    float data[4][4] = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    Matrix4 m4_0{Matrix4::Identity()}, m4_1{data};

    SECTION("Identity") {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    REQUIRE(m4_0.m[i][j] == 1);
                } else {
                    REQUIRE(m4_0.m[i][j] == 0);
                }
            }
        }
    }

    SECTION("Addition") {
        Matrix4 result = m4_0 + m4_1;
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
        Matrix4 result = m4_0 - m4_1;
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
        Matrix4 result = m4_0 * m4_1;
        REQUIRE(result == m4_1);
    }

    SECTION("Scalar multiplication") {
        Matrix4 result = m4_0 * 2.0f;
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
        Matrix4 result = m4_0 / 2.0f;
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
        Matrix4 result = m4_1.Transpose();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                REQUIRE(result.m[i][j] == m4_1.m[j][i]);
            }
        }
    }

    float data2[2][2]{{1, 2}, {3, 4}};
    Matrix2 m2 = Matrix2(data2);
    float data3[3][3]{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3 m3 = Matrix3(data3);

    SECTION("Determinant") {
        REQUIRE(m2.Determinant() == -2);
        REQUIRE(m3.Determinant() == 0);
        REQUIRE(m4_1.Determinant() == 0);
    }

    SECTION("Inverse") {
        auto m2t = m2.Inverse();
        REQUIRE(m2t.has_value());
        float data2[2][2]{{-2, 1}, {1.5, -0.5}};
        Matrix2 m2t_check = Matrix2(data2);
        REQUIRE(m2t.value() == m2t_check);
    }
}
