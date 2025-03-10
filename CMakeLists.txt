cmake_minimum_required(VERSION 3.16)

project(SDL_Zeldalike)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external/sdl2)
target_include_directories(${PROJECT_NAME}
    PUBLIC external/sdl2/include)
target_link_directories(${PROJECT_NAME}
    PRIVATE build/external/sdl2)
target_link_libraries(${PROJECT_NAME} SDL2)