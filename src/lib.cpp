#include "utils.h"

double utils::degree_to_radian(double degree) {
    return degree * (utils::M_PI / 180);
}
double utils::radian_to_degree(double radian) {
    return radian * (180 / utils::M_PI);
}
