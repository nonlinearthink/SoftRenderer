file(GLOB_RECURSE softrenderer_header_files "include/*.h" "include/*.hpp")
file(GLOB_RECURSE softrenderer_source_files "src/*.cpp")

message("SoftRenderer Header Files: ${softrenderer_header_files}")
message("SoftRenderer Source Files: ${softrenderer_source_files}")

if(WIN32)
    # Entry for Windows
    message("Build Windows Version")
    add_executable(
        SoftRenderer 
        WIN32 
        windows.cpp
        ${softrenderer_header_files} 
        ${softrenderer_source_files}
    )
    target_include_directories(SoftRenderer PUBLIC include)
    target_compile_features(SoftRenderer PUBLIC cxx_std_17)
elseif(APPLE)
    # Entry for macOS
    message("Build macOS Version")
    add_executable(SoftRenderer macos.cpp)
endif()

# target_link_libraries(SoftRenderer PRIVATE RenderBase)
target_compile_features(SoftRenderer PRIVATE cxx_std_17)
