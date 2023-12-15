#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "SoftRenderer.h"

int main() {
    SoftRenderer::ObjLoader loader("assets/cube.obj");

    loader.LoadModel();

    return 0;
}
