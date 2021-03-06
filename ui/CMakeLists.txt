project(dct_ui)
cmake_minimum_required(VERSION 2.8)

SET (CMAKE_CXX_FLAGS "-Wall -std=c++11 -ldl")

find_package(OpenGL)
find_package(glfw3 3.2 REQUIRED)

include_directories(deps/imgui-1.52)
include_directories(deps/imgui-1.52/examples/libs/gl3w)

set(SOURCES
	# old opengl
	main_gl2.cpp
	imgui_impl_glfw_gl2.cpp
	
	# modern opengl
	#main_gl3.cpp
	#imgui_impl_glfw_gl3.cpp
	#deps/imgui-1.52/examples/libs/gl3w/GL/gl3w.c

	mainwindow.cpp
	utils.cpp
	
	# non-ui code (dct math from the console application)
	../input.cpp
	../output.cpp
	../dct.cpp
	
	# imgui
	deps/imgui-1.52/imgui.cpp
	deps/imgui-1.52/imgui_demo.cpp
	deps/imgui-1.52/imgui_draw.cpp
)

add_executable(dct_ui ${SOURCES})

TARGET_LINK_LIBRARIES(dct_ui
    dl
	glfw
	${GLFW_LIBRARIES}
	${OPENGL_LIBRARIES}
)
