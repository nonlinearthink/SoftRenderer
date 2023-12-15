#pragma once

#include <string>
#include <vector>

#include "SoftRenderer/math/transform.h"
#include "SoftRenderer/math/vec.hpp"
#include "SoftRenderer/scene/vertex.h"

namespace SoftRenderer {
class Mesh {
public:
    Transform transform;

    std::string name;
    std::vector<Vector3f> vertices;
    std::vector<Vector3f> normal;
    std::vector<Vector2f> uv;
    std::vector<unsigned int> indices;

    Mesh() = default;
    Mesh(std::string _name) : name(_name) {}
    ~Mesh() = default;
};
}  // namespace SoftRenderer
