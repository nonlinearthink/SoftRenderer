cmake_minimum_required(VERSION 3.21)
project(SoftEngine VERSION 0.1.0 LANGUAGES CXX)

# Generate compile_commands.json for clangd LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMake Debug
# set(CMAKE_VERBOSE_MAKEFILEON ON)

add_subdirectory(third_party)

add_subdirectory(renderer)

add_subdirectory(app)

include(CTest)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
