#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SoftRenderer/mesh.h"

namespace SoftRenderer {
// ObjLoader Class
// Load .obj model file and .mtl material file to scene
class ObjLoader {
public:
    explicit ObjLoader(std::string path) : path_{std::move(path)}, world_{} {};

    bool LoadModel();

private:
    std::string path_;
    std::vector<std::shared_ptr<SoftRenderer::Mesh>> world_{};
};
}  // namespace SoftRenderer
