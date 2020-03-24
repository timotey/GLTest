#version 330 core

layout(triangles) in;
layout (triangle_strip, max_vertices = 3) out;
smooth out vec3 g_Normal;
in vec3 v_FragPos[];
smooth out vec3 g_FragPos;
in vec2 v_TexCoord[];
smooth out vec2 g_TexCoord;

void main()
{
	g_Normal = normalize(cross(v_FragPos[1] - v_FragPos[0], v_FragPos[2] - v_FragPos[0]));
    for(int i = 0;i < gl_in.length();i++)
    {
        g_FragPos = v_FragPos[i];
        g_TexCoord = v_TexCoord[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
};