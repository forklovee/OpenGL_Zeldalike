# Zeldalike in OpenGL

<b>Not finished yet.</b>

It's my learning ground for C++, OpenGL, GLAD, GLFW and CMake.

Will see how it goes.

## Current State


https://github.com/user-attachments/assets/46d75230-2244-4d45-9c90-4522a1b9303c




### What works?
- Resizing viewport size as the framebuffer's size changes
- Input. You can close the window by pressing Esc
- Drawing shapes from Vertex Data
- Vertex Position and Vertex Color stored in a single VBO
- Indexed drawing using EBO
- Vertex and Fragment shaders getting inputs from CPU and passing data to each other (such as Vertex Color), also working shader uniform (wow.)
- Image loading with stb_image
- Using multiple textures in fragment shader
- PVM matrices (aka Projection, View and Model transformations)

## Building
Requires C++ 17 compiler, git and CMake.

1) Go to root directory
2) Initialize and update submodules
```sh
git submodule init
git submodule update
```

3) Run cmake
```sh
cmake
```
## Running
After building, the executabe will be in the "build" folder.
