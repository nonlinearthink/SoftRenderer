#include "SoftRenderer/obj_loader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include "SoftRenderer/vec.h"

using namespace SoftRenderer;

bool ObjLoader::LoadModel() {
    std::ifstream file{path_};

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    std::string parse_type;
    char line[1024];
    std::istringstream line_iss;
    std::shared_ptr<Mesh> mesh = nullptr;
    while (file.good()) {
        file.getline(line, 1023);
        line_iss.clear();
        line_iss.str(line);

        if (!(line_iss >> parse_type)) {
            continue;
        }
        if (parse_type == "o") {
            mesh = std::make_shared<Mesh>();
            world_.push_back(mesh);
            line_iss >> mesh->name_ref();
        } else if (mesh != nullptr) {
            if (parse_type == "v") {
                Vector3f vertex;
                line_iss >> vertex.x >> vertex.y >> vertex.z;
                mesh->vertices_ref().push_back(vertex);
            } else if (parse_type == "vn") {
                Vector3f normal;
                line_iss >> normal.x >> normal.y >> normal.z;
                mesh->normal_ref().push_back(normal);
            } else if (parse_type == "vt") {
                Vector2f uv;
                line_iss >> uv.x >> uv.y;
                mesh->uv_ref().push_back(uv);
            }
        }
    }

    file.close();

    return true;
}