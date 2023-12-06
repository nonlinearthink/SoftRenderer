add_executable(Triangle triangle.cpp framework.hpp)
target_link_libraries(Triangle PRIVATE SDL2 SoftRenderer)
target_compile_features(Triangle PUBLIC cxx_std_17)
add_custom_command(
    TARGET Triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Triangle> $<TARGET_FILE_DIR:Triangle>
    COMMAND_EXPAND_LISTS
)
