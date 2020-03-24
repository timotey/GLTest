#version 430 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 TexCoord;

uniform mat4 M;
uniform mat4 MVP;

out vec3 v_FragPos;
out vec2 v_TexCoord;

void main()
{
	gl_Position = MVP * position;
    v_FragPos = vec3(M * position);
    v_TexCoord = TexCoord;
};