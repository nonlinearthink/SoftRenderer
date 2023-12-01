# file(GLOB_RECURSE softrenderer_header_files "include/*.h" "include/*.hpp")
# file(GLOB_RECURSE softrenderer_source_files "src/*.cpp")

# message("SoftRenderer Header Files: ${softrenderer_header_files}")
# message("SoftRenderer Source Files: ${softrenderer_source_files}")

add_executable(
    SoftRenderer
    src/main.cpp
    # ${softrenderer_header_files} 
    # ${softrenderer_source_files}
)
target_link_libraries(SoftRenderer PRIVATE SDL2::SDL2-static)
target_include_directories(SoftRenderer PUBLIC include)
target_compile_features(SoftRenderer PUBLIC cxx_std_17)

# target_link_libraries(SoftRenderer PRIVATE RenderBase)
target_compile_features(SoftRenderer PRIVATE cxx_std_17)
