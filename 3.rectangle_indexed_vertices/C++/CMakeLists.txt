cmake_minimum_required(VERSION 3.10)

# set the project name

add_subdirectory(glfw)
add_subdirectory(glad)
project(program)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)  # poti sa folosesti si functii nesigure (ex fopen)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES g dl GL GLU glfw X11 Xxf86vm Xrandr pthread Xi Xinerama Xcursor assimp)
    endif()
endif()

# add include
include_directories(glfw/include/GLFW glad/include)

file(GLOB SOURCES glad/src/glad.c main.cpp)
        
add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")


# add the executable
add_executable(program ${SOURCES})


target_link_libraries(program  glfw ${GLFW_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

