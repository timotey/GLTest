#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube u_c;

void main()
{    
    FragColor = texture(u_c, TexCoords);
}