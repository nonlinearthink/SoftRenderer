#pragma once

#include <cmath>

namespace utils {
const double M_PI = std::acos(-1);

inline double degree_to_radian(double degree) {
    return degree * (utils::M_PI / 180);
}

inline double radian_to_degree(double radian) {
    return radian * (180 / utils::M_PI);
}

}  // namespace utils