cmake_minimum_required(VERSION 3.20)

# option(SOFT_RENDERER_DEV, "Enable the develop mode: build tests, cmake verbose log etc." ON)

project(SoftRenderer VERSION 0.1.0 LANGUAGES CXX)

# if(SOFT_RENDERER_DEV)
include(CTest)

#     # build tests
set(BUILD_TESTING ON)
#     # cmake verbose log
#     set(CMAKE_VERBOSE_MAKEFILEON ON)    
# else()
#     set(BUILD_TESTING OFF)
# endif()

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(third_party)

add_subdirectory(RenderBase)

add_subdirectory(SoftRenderer)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
