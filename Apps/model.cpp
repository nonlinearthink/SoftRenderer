#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "SoftRenderer.h"

int main() {
    SoftRenderer::ObjLoader loader{"assets/cube.obj"};

    std::vector<std::shared_ptr<SoftRenderer::Mesh>> world;

    loader.LoadModel(world);

    return 0;
}
