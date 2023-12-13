macro(AddApp target_name)
    message("${target_name} App sources: ${ARGN}")
    add_executable(${target_name} ${ARGN})
    target_link_libraries(${target_name} PRIVATE SDL2 SoftRenderer)
    target_compile_features(${target_name} PUBLIC cxx_std_17)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${target_name}> $<TARGET_FILE_DIR:${target_name}>
        COMMAND_EXPAND_LISTS
    )
endmacro(AddApp target_name)

AddApp(TriangleApp triangle.cpp framework.hpp)
