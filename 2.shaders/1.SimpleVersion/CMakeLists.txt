cmake_minimum_required(VERSION 3.10)

# set the project name
project(program)

# add the executable
add_executable(program src/glad.c main.c)

# add include
include_directories(./include /usr/include/GL)

# add sources
set(SOURCES src)

#target_link_libraries(program m GL GLEW GLU glut glfw dl)

target_link_libraries(program GL GLEW  m dl glfw)

#-lglut -lGL -lGLEW -lGLU -Wall # -lGL -lglfw3 -lXrandr -lglfw -lXi -lX11 -lXxf86vm -lpthread