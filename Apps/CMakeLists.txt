macro(AddApp target_name)
    if(PRINT_CMAKE_DEBUG_MESSAGE)
        message("${target_name} App sources: ${ARGN}")
    endif()

    add_executable(${target_name} ${ARGN})
    target_link_libraries(${target_name} PRIVATE SDL2 SoftRenderer)
    target_compile_features(${target_name} PUBLIC cxx_std_17)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${target_name}> $<TARGET_FILE_DIR:${target_name}>
        COMMAND_EXPAND_LISTS
    )
endmacro(AddApp target_name)

add_custom_target(CopyAssets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/CopyAssets.cmake
)

AddApp(TriangleDemo triangle.cpp lib/application.h lib/application.cpp)
AddApp(MeshDemo mesh.cpp lib/application.h lib/application.cpp)
add_dependencies(MeshDemo CopyAssets)
