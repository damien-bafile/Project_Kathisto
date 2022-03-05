# CMakeList.txt : CMake project for Project_Kathisto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


set(PROJECT_NAME Project_Kathisto)
project(${PROJECT_NAME} LANGUAGES C)

find_package(OpenGL REQUIRED)

add_subdirectory(src)


# Add source to this project's executable.
add_executable(Project_Kathisto ${SOURCES} "src/main.c")

add_subdirectory(lib)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

target_link_libraries(${PROJECT_NAME} PUBLIC freeglut_static)