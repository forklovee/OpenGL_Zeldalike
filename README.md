# Zeldalike in OpenGL

<b>Not finished yet.</b>

It's my learning ground for C++, OpenGL, GLAD, GLFW and CMake.

Will see how it goes.

## Current State

https://github.com/user-attachments/assets/23afb3c0-970e-486a-8c39-67791b052c26

### What works?
- Resizing viewport size as the framebuffer's size changes
- Input. You can close the window by pressing Esc
- Drawing shapes from Vertex Data
- Vertex Position and Vertex Color stored in a single VBO
- Indexed drawing using EBO
- Vertex and Fragment shaders getting inputs from CPU and passing data to each other (such as Vertex Color), also working shader uniform (wow.)
- Image loading with stb_image
- Using multiple textures in fragment shader

## Building
CMake takes care of everything.

Just run `cmake` in the root directory.

## Running
After building, the executabe will be in the "build" folder.
