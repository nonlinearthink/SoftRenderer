macro(AddTest target_name)
    add_executable(${target_name} ${target_name}.cpp)
    target_compile_features(${target_name} PUBLIC cxx_std_17)
    target_link_libraries(${target_name} PRIVATE Catch2::Catch2WithMain SoftRenderer)
    add_test(NAME ${target_name} COMMAND $<TARGET_FILE:${target_name}>)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${target_name}> $<TARGET_FILE_DIR:${target_name}>
        COMMAND_EXPAND_LISTS
    )
endmacro(AddTest target_name)

AddTest(common_tests)
AddTest(math_vec_tests)
AddTest(math_matrix_tests)
