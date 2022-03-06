add_subdirectory(math)
add_subdirectory(game)
add_subdirectory(window)


set(SOURCES
    src/main.c
    ${MATH}
    ${GAME}
    ${WINDOW}
    PARENT_SCOPE)