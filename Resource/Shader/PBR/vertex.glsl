#version 430 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in mat4 MV;
uniform mat4 P;

out vec2 v_TexCoord;
out vec3 v_FragPos;

void main()
{
	gl_Position = P * MV * position;
    v_FragPos = vec3(MV * position);
    v_TexCoord = TexCoord;
};