cmake_minimum_required(VERSION 3.10)

# set the project name
project("Shaders")

set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Dependencies/vendor/glfw)


add_subdirectory(Dependencies/vendor/glad)


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
include_directories(Dependencies/vendor/glfw/include/GLFW Dependencies/vendor/glad/include/ Dependencies/include)

# add sources
file(GLOB SOURCES
		Dependencies/src/*.c* Dependencies/vendor/glad/src/glad.c)
file(GLOB HEADERS Dependencies/include/*.h)

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})


set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
