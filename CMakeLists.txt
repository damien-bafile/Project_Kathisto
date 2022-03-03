# CMakeList.txt : CMake project for Project_Kathisto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


set(PROJECT_NAME Project_Kathisto)
project(${PROJECT_NAME} LANGUAGES C)

# find_package(OpenGL REQUIRED)

add_subdirectory(src)


# Add source to this project's executable.
add_executable (Project_Kathisto "src/main.c" )

# TODO: Add tests and install targets if needed.
