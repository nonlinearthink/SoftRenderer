if(WIN32)
    # Entry for Windows
    message("Build Windows Version")
    add_executable(SoftRenderer WIN32 src/windows.cpp)
elseif(APPLE)
    # Entry for macOS
    message("Build macOS Version")
    add_executable(SoftRenderer src/macos.cpp)
endif()

# target_link_libraries(SoftRenderer PRIVATE RenderBase)
target_compile_features(SoftRenderer PRIVATE cxx_std_17)
