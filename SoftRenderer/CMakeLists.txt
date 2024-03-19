set(
    SOFTRENDERER_FILES
    include/SoftRenderer/camera.h
    include/SoftRenderer/color.h
    include/SoftRenderer/common.h
    include/SoftRenderer/matrix.h
    include/SoftRenderer/mesh.h
    include/SoftRenderer/obj_loader.h
    include/SoftRenderer/renderer.h
    include/SoftRenderer/scene.h
    include/SoftRenderer/shader_context.h
    include/SoftRenderer/shader_program.h
    include/SoftRenderer/shader_variable.h
    include/SoftRenderer/transform.h
    include/SoftRenderer/vec.h
    include/SoftRenderer/vertex.h
    include/SoftRenderer.h
    src/camera.cpp
    src/common.cpp
    src/obj_loader.cpp
    src/renderer.cpp
    src/scene.cpp
    src/transform.cpp
)

if(PRINT_CMAKE_DEBUG_MESSAGE)
    message("SoftRenderer Header&Source Files: ${SOFTRENDERER_FILES}")
endif()

add_library(SoftRenderer SHARED ${SOFTRENDERER_FILES})
target_include_directories(SoftRenderer PUBLIC include)
set_target_properties(SoftRenderer PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(SoftRenderer PUBLIC cxx_std_17)
set_target_properties(SoftRenderer PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    message("Build Tests...")
    enable_testing()
    add_subdirectory(tests)
endif()
