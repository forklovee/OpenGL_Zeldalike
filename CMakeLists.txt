cmake_minimum_required(VERSION 3.16)

project(SimpleOpenGL_App)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    external/glad/src/glad.c)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glad/include)

# target_link_directories(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)