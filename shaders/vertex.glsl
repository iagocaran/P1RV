#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 aColor;

out vec2 TexCoords;
out vec4 Color;

uniform mat4 modelview;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    Color = aColor;
    gl_Position = projection * modelview * vec4(aPos, 1.0);
}