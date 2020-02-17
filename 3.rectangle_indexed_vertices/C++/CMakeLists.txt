cmake_minimum_required(VERSION 3.10)

# set the project name
project(testnr1)

# add the executable
add_executable(testnr1 src/glad.c main.cpp)

# add include
include_directories(./include /usr/include/GL)

# add sources
set(SOURCES src)

#target_link_libraries(testnr1 m GL GLEW GLU glut glfw dl)

target_link_libraries(testnr1 GL GLEW  m dl glfw)

#-lglut -lGL -lGLEW -lGLU -Wall # -lGL -lglfw3 -lXrandr -lglfw -lXi -lX11 -lXxf86vm -lpthread