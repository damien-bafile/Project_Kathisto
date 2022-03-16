# CMakeList.txt : CMake project for Project_Kathisto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


set(PROJECT_NAME Project_Kathisto)
project(${PROJECT_NAME} LANGUAGES C)



find_package(OpenGL REQUIRED)

add_subdirectory(src)

# Add source to this project's executable.
add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(lib)

# CIMGUI



if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/backends)
	set(BAKENDS_FOLDER "lib/cimgui/imgui/backends/")
else()
	set(BAKENDS_FOLDER "lib/cimgui/imgui/examples/")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/cimgui/imgui/imgui_tables.cpp)
	set(TABLES_SOURCE "lib/cimgui/imgui/imgui_tables.cpp")
else()
	set(TABLES_SOURCE "")
endif()

include_directories(lib/cimgui/imgui)
add_definitions("-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1")

include_directories(lib/cimgui)
set(IMGUI_SOURCES lib/cimgui/cimgui.cpp 
lib/cimgui/imgui/imgui.cpp 
lib/cimgui/imgui/imgui_draw.cpp 
lib/cimgui/imgui/imgui_demo.cpp 
lib/cimgui/imgui/imgui_widgets.cpp
${TABLES_SOURCE} 
)

if (WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else(WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" ")
endif(WIN32)

add_compile_definitions("IMGUI_IMPL_OPENGL_LOADER_GLUT")


list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_glut.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_SOURCES})

##

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

target_link_libraries(${PROJECT_NAME} PUBLIC freeglut_static)
