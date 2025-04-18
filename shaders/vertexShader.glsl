#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColorData;
layout (location = 2) in vec2 vertexUvData;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;
out vec2 uv;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   vertexColor = vec4(vertexColorData, 1.0);
   uv = vertexUvData;
}