#pragma once

#include <string>
#include <vector>

#include "SoftRenderer/mesh.h"

namespace SoftRenderer {
// ObjLoader Class
// Load .obj model file and .mtl material file to scene
class ObjLoader {
public:
    explicit ObjLoader(std::string path) : path_{std::move(path)} {};

    bool LoadModel(std::vector<std::shared_ptr<Mesh>>& world);

private:
    std::string path_;
};
}  // namespace SoftRenderer
