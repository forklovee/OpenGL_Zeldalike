#version 330 core

out vec4 FragColor;
in vec4 vertexColor;
in vec2 uv;

uniform vec4 modulate;
uniform sampler2D colorTexture;

void main()
{
    FragColor = texture(colorTexture, uv);
    FragColor *= vertexColor * modulate;
}