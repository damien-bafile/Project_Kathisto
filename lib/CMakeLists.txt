

add_compile_options(
    # GCC
    $<$<C_COMPILER_ID:GNU>:-w>
    # Visual Studio
    $<$<C_COMPILER_ID:MSVC>:/W0>
)

add_subdirectory(freeglut)
add_subdirectory(cimgui)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cimgui/imgui/backends)
	set(BAKENDS_FOLDER "cimgui/imgui/backends/")
else()
	set(BAKENDS_FOLDER "cimgui/imgui/examples/")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../imgui/imgui_tables.cpp)
	set(TABLES_SOURCE "cimgui/imgui/imgui_tables.cpp")
else()
	set(TABLES_SOURCE "")
endif()

include_directories(cimgui/imgui)
add_definitions("-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1")

include_directories(cimgui)
set(IMGUI_SOURCES cimgui/cimgui.cpp 
cimgui/imgui/imgui.cpp 
cimgui/imgui/imgui_draw.cpp 
cimgui/imgui/imgui_demo.cpp 
cimgui/imgui/imgui_widgets.cpp
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
	list(APPEND IMGUI_SOURCES cimgui/imgui/misc/freetype/imgui_freetype.cpp)
	add_definitions("-DCIMGUI_FREETYPE=1")
endif(IMGUI_FREETYPE)


#opengl2
list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_glut.cpp)
list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_opengl2.cpp)

add_library(${PROJECT_NAME} SHARED ${IMGUI_SOURCES})
target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARIES} ${IMGUI_SDL_LIBRARY})

target_compile_definitions(cimgui PRIVATE 
	IMGUI_IMPL_API=extern\ \"C\"
	IMGUI_IMPL_OPENGL_LOADER_GLUT)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    freeglut/include
    cimgui
	cimgui/generator/output/
    )