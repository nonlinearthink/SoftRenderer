add_executable(SoftRenderer src/main.cpp)
target_link_libraries(SoftRenderer PRIVATE SDL2)
target_compile_features(SoftRenderer PUBLIC cxx_std_17)
add_custom_command(
    TARGET SoftRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SoftRenderer> $<TARGET_FILE_DIR:SoftRenderer>
    COMMAND_EXPAND_LISTS
)
