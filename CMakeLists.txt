cmake_minimum_required(VERSION 3.16)

project(SimpleOpenGL_App)

set(CMAKE_CXX_VERSION 17)

find_package(OpenGL REQUIRED)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_executable(${PROJECT_NAME}
    src/main.cpp
    external/glad/src/glad.c
)

target_sources(${PROJECT_NAME}
    PRIVATE src/private/app.cpp
    PRIVATE src/private/mesh.cpp
    PRIVATE src/private/meshinstance.cpp
    PRIVATE src/private/Shader/shader.cpp
    PRIVATE src/private/texture.cpp
    PRIVATE src/private/camera.cpp
    
)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glad/include
    PUBLIC src/public
    PUBLIC external/stb_image
)

target_link_directories(${PROJECT_NAME}
    PRIVATE external/stb_image
)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw glm)