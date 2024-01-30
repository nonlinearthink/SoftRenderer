#include "SoftRenderer/scene.h"

#include "SoftRenderer/obj_loader.h"

using namespace SoftRenderer;

bool Scene::LoadAssetsFromFile(const std::string &path) {
    if (StringUtils::EndsWith(path, ".obj")) {
        ObjLoader loader{path};
        loader.LoadModel(world_);
    }
    return true;
}
