#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SoftRenderer/mesh.h"
#include "SoftRenderer/obj_loader.h"


namespace SoftRenderer {
class Scene {
public:
    bool LoadAssetsFromFile(std::string path);

private:
    std::vector<std::shared_ptr<SoftRenderer::Mesh>> world_;
};
};  // namespace SoftRenderer
