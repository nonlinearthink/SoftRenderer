file(GLOB_RECURSE renderer_source_files "src/*.cpp")
file(GLOB_RECURSE renderer_header_files "include/*.h")

message("Renderer Source Files: ${renderer_source_files}")
message("Renderer Header Files: ${renderer_header_files}")

add_library(renderer STATIC ${renderer_header_files} ${renderer_source_files})
target_include_directories(renderer PUBLIC include)
target_compile_features(renderer PUBLIC cxx_std_17)
