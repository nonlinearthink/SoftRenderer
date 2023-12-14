#pragma once

#include <vector>

#include "SoftRenderer/math/transform.h"
#include "SoftRenderer/scene/vertex.h"

namespace SoftRenderer {
class Mesh {
public:
    Transform transform;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
}  // namespace SoftRenderer
