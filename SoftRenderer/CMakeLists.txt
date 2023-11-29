add_executable(SoftRenderer src/main.cpp)
# target_link_libraries(SoftRenderer PRIVATE RenderBase)
target_compile_features(SoftRenderer PRIVATE cxx_std_17)
