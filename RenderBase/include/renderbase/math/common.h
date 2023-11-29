#pragma once

#include <cmath>

namespace RenderBase {

const double PI = std::acos(-1);

inline double degree_to_radian(double degree) {
    return degree * (RenderBase::PI / 180);
}

inline double radian_to_degree(double radian) {
    return radian * (180 / RenderBase::PI);
}

}  // namespace RenderBase
