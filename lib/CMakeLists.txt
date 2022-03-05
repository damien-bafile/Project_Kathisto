

add_compile_options(
    # GCC
    $<$<C_COMPILER_ID:GNU>:-w>
    # Visual Studio
    $<$<C_COMPILER_ID:MSVC>:/W0>
)

add_subdirectory(freeglut)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    freeglut/include
    )