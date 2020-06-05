#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 u_P;
uniform mat4 u_V;

void main()
{
    TexCoords = aPos;
    gl_Position = u_P * u_V * vec4(aPos, 1.0);
}  