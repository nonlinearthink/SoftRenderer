#pragma once

#include <string>
#include <vector>

#include "SoftRenderer/camera.h"
#include "SoftRenderer/mesh.h"

namespace SoftRenderer {
class Scene {
public:
    bool LoadAssetsFromFile(const std::string &path);

private:
    std::vector<std::shared_ptr<SoftRenderer::Mesh>> world_;
    std::unique_ptr<Camera> camera_{nullptr};
};
};  // namespace SoftRenderer
