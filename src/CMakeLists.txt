add_library(renderer_core STATIC lib.cpp)
target_include_directories(renderer_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_features(renderer_core PUBLIC cxx_std_17)

add_executable(renderer main.cpp)
target_include_directories(renderer PRIVATE renderer_core)
target_compile_features(renderer PRIVATE cxx_std_17)
