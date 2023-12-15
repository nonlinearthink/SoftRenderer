cmake_minimum_required(VERSION 3.20)

option(PRINT_CMAKE_DEBUG_MESSAGE "Print message" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILEON OFF)

project(SoftRenderer VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

add_subdirectory(ThirdParty)
add_subdirectory(SoftRenderer)
add_subdirectory(Apps)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
