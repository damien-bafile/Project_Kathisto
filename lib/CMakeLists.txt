

add_compile_options(
    # GCC
    $<$<C_COMPILER_ID:GNU>:-w>
    # Visual Studio
    $<$<C_COMPILER_ID:MSVC>:/W0>
)

add_subdirectory(freeglut)
add_subdirectory(cimgui)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    freeglut/include
    cimgui
    )