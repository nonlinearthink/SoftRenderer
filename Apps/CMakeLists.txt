add_executable(DrawTriangle main.cpp)
target_link_libraries(DrawTriangle PRIVATE SDL2 SoftRenderer)
target_compile_features(DrawTriangle PUBLIC cxx_std_17)
add_custom_command(
    TARGET DrawTriangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:DrawTriangle> $<TARGET_FILE_DIR:DrawTriangle>
    COMMAND_EXPAND_LISTS
)
