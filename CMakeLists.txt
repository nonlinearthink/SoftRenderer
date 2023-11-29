cmake_minimum_required(VERSION 3.20)

project(SoftRenderer VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# cmake verbose log
set(CMAKE_VERBOSE_MAKEFILEON OFF)    

add_subdirectory(third_party)

add_subdirectory(RenderBase)

add_subdirectory(SoftRenderer)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
