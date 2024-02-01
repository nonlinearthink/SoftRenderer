#include "SoftRenderer/shader_program.h"

using namespace SoftRenderer;

Vector3f StandShaderProgram::VertexShader(const Vertex &vertex,
                                          EmptyShaderContext &context) {
    return Vector3f{vertex.position};
}

Color StandShaderProgram::PixelShader(const EmptyShaderContext &context) {
    return Color::White();
}
