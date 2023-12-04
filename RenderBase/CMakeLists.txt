file(GLOB_RECURSE rendererbase_header_files "include/*.h" "include/*.hpp")
file(GLOB_RECURSE rendererbase_source_files "src/*.cpp")

message("RenderBase Header Files: ${rendererbase_header_files}")
message("RenderBase Source Files: ${rendererbase_source_files}")

add_library(RenderBase SHARED ${rendererbase_source_files} ${rendererbase_header_files})
target_include_directories(RenderBase PUBLIC include)
set_target_properties(RenderBase PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(RenderBase PUBLIC cxx_std_17)
set_target_properties(RenderBase PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(RenderBase PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    message("Build Tests...")
    enable_testing()
    add_subdirectory(tests)
endif()
