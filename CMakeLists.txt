cmake_minimum_required(VERSION 3.21)
project(SoftEngine VERSION 0.1.0 LANGUAGES CXX)

# Generate compile_commands.json for clangd LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CMake Debug
# set(CMAKE_VERBOSE_MAKEFILEON ON)

add_subdirectory(third_party)

include(CTest)
add_subdirectory(Renderlib)

add_subdirectory(SoftRenderer)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
