add_executable(SoftRenderer main.cpp)
# target_link_libraries(SoftRenderer PRIVATE Renderlib)
target_compile_features(SoftRenderer PRIVATE cxx_std_17)
