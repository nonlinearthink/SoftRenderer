file(GLOB_RECURSE renderer_header_files "include/*.h" "include/*.hpp")
# file(GLOB_RECURSE renderer_source_files "src/*.cpp")

message("Renderer Header Files: ${renderer_header_files}")
# message("Renderer Source Files: ${renderer_source_files}")

add_library(Renderlib ${renderer_header_files})
target_include_directories(Renderlib PUBLIC include)
set_target_properties(Renderlib PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Renderlib PUBLIC cxx_std_17)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    message("Build Tests")
    enable_testing()
    add_subdirectory(tests)
endif()
