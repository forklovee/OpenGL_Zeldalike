#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColorData;
layout (location = 2) in vec2 vertexUvData;

out vec4 vertexColor;
out vec2 uv;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vertexColor = vec4(vertexColorData, 1.0);
   uv = vertexUvData;
}