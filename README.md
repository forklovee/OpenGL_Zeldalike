# Zeldalike in OpenGL

<b>Not finished yet.</b>

It's my learning ground for C++, OpenGL, GLAD, GLFW and CMake.

Will see how it goes.

## Current State

https://github.com/user-attachments/assets/6e05a3ab-17f5-4a3f-a09c-893b0ec510cd

### Features
- Resizing viewport size as the framebuffer's size changes
- Input. You can close the window by pressing Esc
- Drawing shapes from Vertex Data
- Vertex Position and Vertex Color stored in a single VBO
- Indexed drawing using EBO
- Vertex and Fragment shaders getting inputs from CPU and passing data to each other (such as Vertex Color), also working shader uniform (wow.)
- Image loading with stb_image
- Using multiple textures in fragment shader
- PVM matrices (aka Projection, View and Model transformations)
- Camera movement by user input (no rotation yet)

### Controls
Esc - Quit

WSAD - Move camera

## Building
Requires C++ 17 compiler, git and CMake.

1) Go to root directory
2) Initialize and update submodules
```sh
git submodule init
git submodule update
```

3) Create "build" folder
```sh
mkdir build
```

4) Run CMake
```sh
cmake . -B ./build
```
  
6) Run MakeFile in "build" folder
```sh
cd build
make
```

## Running
After building, the executabe will be in the "build" folder.
