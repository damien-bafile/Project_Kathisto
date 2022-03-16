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

set(imgui_impl )


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

set(IMGUI_LIBRARIES )

if (WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else(WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" ")
endif(WIN32)

add_compile_definitions("IMGUI_IMPL_OPENGL_LOADER_GLUT")

#optional adding freetype
option(IMGUI_FREETYPE "add Freetype2" OFF)

if(IMGUI_FREETYPE)
	FIND_PACKAGE(freetype REQUIRED PATHS ${FREETYPE_PATH})
	list(APPEND IMGUI_LIBRARIES freetype)
	list(APPEND IMGUI_SOURCES lib/cimgui/imgui/misc/freetype/imgui_freetype.cpp)
	add_definitions("-DCIMGUI_FREETYPE=1")
endif(IMGUI_FREETYPE)


#opengl2
list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_glut.cpp)
list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_opengl2.cpp)

add_library(${imgui_impl} SHARED ${IMGUI_SOURCES})


target_compile_definitions(cimgui PRIVATE 
	IMGUI_IMPL_API=extern\ \"C\"
	IMGUI_IMPL_OPENGL_LOADER_GLUT)

target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARIES} ${imgui_impl})



#set(cimgui lib/cimgui)
#set(imgui_impl ${cimgui}/imgui/backends)

#include_directories(${cimgui})
#include_directories(${cimgui}/imgui)
#include_directories(${imgui_impl})

# add_library(imgui_impl STATIC ${imgui_impl}/imgui_impl_opengl2.cpp ${imgui_impl}/imgui_impl_glut.cpp)
#add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLUT)
#target_compile_definitions(imgui_impl PRIVATE IMGUI_IMPL_API=extern\ \"C\")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

target_link_libraries(${PROJECT_NAME} PUBLIC freeglut_static)

target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_API=)

