#version 430 core
layout(location = 0) in vec4 position;
smooth out vec2 texCoord;

void main()
{
	gl_Position = position;
	texCoord = (position.xy+vec2(1))/2;
};