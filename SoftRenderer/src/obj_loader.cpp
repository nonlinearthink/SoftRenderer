#include "SoftRenderer/obj_loader.h"

#include <memory>

#include "SoftRenderer/vec.h"

using namespace SoftRenderer;

bool ObjLoader::LoadModel(std::vector<std::shared_ptr<Mesh>>& world) {
    std::ifstream file{path_};

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    auto line = std::unique_ptr<char[]>(new char[1024]);
    std::istringstream line_iss;
    std::string parse_type;
    std::shared_ptr<Mesh> mesh{nullptr};
    while (file.good()) {
        file.getline(line.get(), 1023);
        line_iss.clear();
        line_iss.str(line.get());

        if (!(line_iss >> parse_type)) {
            continue;
        }
        if (parse_type == "o") {
            mesh = std::make_shared<Mesh>();
            world.push_back(mesh);
            line_iss >> mesh->name_;
        } else if (mesh != nullptr) {
            if (parse_type == "v") {
                auto vertex = std::make_shared<Vector3f>();
                line_iss >> vertex->x >> vertex->y >> vertex->z;
                mesh->vertices_.push_back(vertex);
            } else if (parse_type == "vn") {
                auto normal = std::make_shared<Vector3f>();
                line_iss >> normal->x >> normal->y >> normal->z;
                mesh->normals_.push_back(normal);
            } else if (parse_type == "vt") {
                auto uv = std::make_shared<Vector2f>();
                line_iss >> uv->x >> uv->y;
                mesh->texure_coordinates_.push_back(uv);
            } else if (parse_type == "f") {
                std::string face_token;
                while (line_iss >> face_token) {
                    std::istringstream face_token_iss{face_token};
                    int index;

                    // Read vertex indices
                    face_token_iss >> index;
                    mesh->vertex_indices_.push_back(index - 1);

                    char slash;
                    bool has_texture_indices{false};
                    // Try to read texture indices
                    if (face_token_iss >> slash && slash == '/') {
                        face_token_iss >> index;
                        mesh->texture_indices_.push_back(index - 1);
                        has_texture_indices = true;
                    } else {
                        mesh->texture_indices_.push_back(-1);
                    }

                    // Try to read normal indices
                    if (has_texture_indices && face_token_iss >> slash &&
                        slash == '/') {
                        face_token_iss >> index;
                        mesh->normal_indices_.push_back(index - 1);
                    } else {
                        mesh->normal_indices_.push_back(-1);
                    }
                }
            }
        }
    }

    file.close();

    return true;
}