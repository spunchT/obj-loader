cmake_minimum_required(VERSION 3.20)
project(obj-loader LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)

FetchContent_MakeAvailable(glfw glad)

glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE API gl:core=4.6)

find_package(OpenGL REQUIRED)

add_executable(obj-loader src/main.cpp)

target_link_libraries(obj-loader PRIVATE
    glfw
    glad_gl_core_46
    OpenGL::GL
)
