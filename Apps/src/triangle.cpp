// Set SDL Main Entry Point
#define SDL_MAIN_HANDLED

#include <memory>
#include <vector>

#include "SDLApplication.h"
#include "SoftRenderer.h"

using namespace SoftRenderer;

class TriangleShaderProgram : public IShaderProgram {
public:
    Vector3f VertexShader(const Vertex &vertex,
                          ShaderContext &context) override {
        context.varring_color[FRAG_COLOR_BINDING] = vertex.color;
        return vertex.position;
    }
    Color PixelShader(const ShaderContext &context) override {
        return context.varring_color.at(FRAG_COLOR_BINDING);
    }

private:
    static u32 FRAG_COLOR_BINDING;
};

int main(int argc, char *argv[]) {
    std::vector<Vertex> vertex_buffer = {
        {{0., 0.7, 0.9}, {0., 1., 0.}, {0., 0.}, {1., 0., 0., 1.}},
        {{-0.6, -0.2, 0.01}, {0., 1., 0.}, {0., 0.}, {0., 1., 0., 1.}},
        {{+0.6, -0.2, 0.01}, {0., 1., 0.}, {0., 0.}, {0., 0., 1., 1.}}};

    auto renderer = std::make_unique<SoftRenderer::Renderer>(800, 600);
    renderer->set_vertex_buffer(vertex_buffer);
    renderer->set_shader_program(std::make_unique<TriangleShaderProgram>());

    auto app = std::make_unique<SDLApplication>("Shaded Triangle", renderer);
    if (!app->Initialize()) {
        return 1;
    }
    app->MainLoop();
    app->Destroy();

    return 0;
}
