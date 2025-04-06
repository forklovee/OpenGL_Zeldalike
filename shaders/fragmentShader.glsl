#version 330 core

out vec4 FragColor;
in vec4 vertexColor;
in vec2 uv;

uniform vec4 modulate;
uniform sampler2D colorTexture1;
uniform sampler2D colorTexture2;

void main()
{
    FragColor = mix(texture(colorTexture1, uv), texture(colorTexture2, uv), 0.25);
    FragColor *= vertexColor * modulate;
}