set(SOURCES
    src/main.c
   
    PARENT_SCOPE)


add_library(myLib "")

add_subdirectory(math)
add_subdirectory(game)
add_subdirectory(window)


