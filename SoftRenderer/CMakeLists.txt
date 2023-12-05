file(GLOB_RECURSE SOFTRENDERER_HEADER_FILES "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOFTRENDERER_SOURCE_FILES "src/*.cpp")

set(SOFTRENDERER_HEADERS ${SOFTRENDERER_HEADER_FILES})
set(SOFTRENDERER_SOURCES ${SOFTRENDERER_SOURCE_FILES})

message("SoftRenderer Header Files: ${SOFTRENDERER_HEADERS}")
message("SoftRenderer Source Files: ${SOFTRENDERER_SOURCES}")

add_library(SoftRenderer SHARED ${SOFTRENDERER_HEADERS} ${SOFTRENDERER_SOURCES})
target_include_directories(SoftRenderer PUBLIC include)
set_target_properties(SoftRenderer PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(SoftRenderer PUBLIC cxx_std_17)
set_target_properties(SoftRenderer PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    message("Build Tests...")
    enable_testing()
    add_subdirectory(tests)
endif()
