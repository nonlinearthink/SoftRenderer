#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SoftRenderer/camera.h"
#include "SoftRenderer/mesh.h"
#include "SoftRenderer/obj_loader.h"

namespace SoftRenderer {
class Scene {
public:
    bool LoadAssetsFromFile(std::string path);

private:
    std::vector<std::shared_ptr<SoftRenderer::Mesh>> world_;
    std::unique_ptr<Camera> camera_;
};
};  // namespace SoftRenderer
