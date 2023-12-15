#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SoftRenderer/scene/mesh.h"

namespace SoftRenderer {
/**
 * @brief ObjLoader Class
 * Load .obj model file and .mtl material file to scene
 */
class ObjLoader {
public:
    ObjLoader(std::string path) : path_{path}, world_{} {};

    bool LoadModel();

private:
    std::string path_;
    std::vector<std::shared_ptr<SoftRenderer::Mesh>> world_;
};
}  // namespace SoftRenderer
