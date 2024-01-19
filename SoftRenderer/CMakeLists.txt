set(
    SOFTRENDERER_HEADER_SOURCE_FILES
    include/SoftRenderer/camera.h
    src/camera.cpp
    include/SoftRenderer/obj_loader.h
    src/obj_loader.cpp
    include/SoftRenderer/quaternion.h
    src/quaternion.cpp
    include/SoftRenderer/renderer.h
    src/renderer.cpp
    include/SoftRenderer/scene.h
    src/scene.cpp
    include/SoftRenderer/transform.h
    src/transform.cpp
)
set(
    SOFTRENDERER_NO_SOURCE_HEADER_FILES
    include/SoftRenderer/color.h
    include/SoftRenderer/common.h
    include/SoftRenderer/matrix.h
    include/SoftRenderer/mesh.h
    include/SoftRenderer/vec.h
    include/SoftRenderer.h
)

if(PRINT_CMAKE_DEBUG_MESSAGE)
    message("SoftRenderer Header&Source Files: ${SOFTRENDERER_HEADER_SOURCE_FILES} ${SOFTRENDERER_NO_SOURCE_HEADER_FILES}")
endif()

add_library(SoftRenderer SHARED ${SOFTRENDERER_HEADER_SOURCE_FILES} ${SOFTRENDERER_NO_SOURCE_HEADER_FILES})
target_include_directories(SoftRenderer PUBLIC include)
set_target_properties(SoftRenderer PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(SoftRenderer PUBLIC cxx_std_17)
set_target_properties(SoftRenderer PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    message("Build Tests...")
    enable_testing()
    add_subdirectory(tests)
endif()
