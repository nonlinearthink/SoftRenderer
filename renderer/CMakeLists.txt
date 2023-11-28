file(GLOB_RECURSE renderer_header_files "include/*.h" "include/*.hpp")
file(GLOB_RECURSE renderer_source_files "src/*.cpp")

message("Renderer Header Files: ${renderer_header_files}")
message("Renderer Source Files: ${renderer_source_files}")

add_library(renderer ${renderer_header_files})
target_include_directories(renderer PUBLIC include)
set_target_properties(renderer PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(renderer PUBLIC cxx_std_17)
