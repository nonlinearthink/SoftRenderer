// Set SDL Main Entry Point
#define SDL_MAIN_HANDLED

#include <memory>
#include <vector>

#include "SDL_application.h"
#include "SoftRenderer.h"

using namespace SoftRenderer;

class TriangleShaderProgram : public IShaderProgram {
public:
    Vector3f VertexShader(const Vertex &vertex,
                          ShaderContext &context) override {
        auto frag_color{ShaderVariable<Color>(0, context)};
        frag_color.set(vertex.color);
        return vertex.position;
    }

    Color PixelShader(const ShaderContext &context) override {
        auto frag_color{ShaderVariable<Color>(0, context)};
        return frag_color.get();
    }
};

int main(int argc, char *argv[]) {
    auto app{std::make_unique<SDLApplication>("Shaded Triangle", 800, 600)};
    app->set_initialize_callback([](SoftRenderer::Renderer &renderer) {
        std::vector<Vertex> vertex_buffer{
            {{0., 0.7, 0.9}, {0., 1., 0.}, {0., 0.}, {1., 0., 0., 1.}},
            {{-0.6, -0.2, 0.01}, {0., 1., 0.}, {0., 0.}, {0., 1., 0., 1.}},
            {{0.6, -0.2, 0.01}, {0., 1., 0.}, {0., 0.}, {0., 0., 1., 1.}}};
        std::vector<u32> index_buffer{0, 1, 2};
        std::shared_ptr<IShaderProgram> shader_program{
            std::make_shared<TriangleShaderProgram>()};
        // auto camera = CameraBuilder().Build();

        // renderer.AttachCamera(camera);
        // renderer.set_background(Color::Red());
        // renderer.set_vertex_buffer(vertex_buffer);
        // renderer.set_index_buffer(index_buffer);
        // renderer.set_shader_program(shader_program);
    });
    app->set_render_callback(
        [](SoftRenderer::Renderer &renderer) { renderer.Render(); });
    app->Run();

    return 0;
}
