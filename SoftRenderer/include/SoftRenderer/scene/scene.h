#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SoftRenderer/loader/obj_loader.h"
#include "SoftRenderer/scene/mesh.h"

namespace SoftRenderer {
class Scene {
public:
    Scene() {}
    ~Scene() {}

    bool LoadAssetsFromFile(std::string path);

private:
    std::vector<std::shared_ptr<SoftRenderer::Mesh>> world_;
};
};  // namespace SoftRenderer
