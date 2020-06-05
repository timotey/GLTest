#version 330 core

layout(triangles) in;
layout (triangle_strip, max_vertices = 3) out;
in vec2 v_TexCoord[];
smooth out vec2 g_TexCoord;
in vec3 v_FragPos[];
smooth out vec3 g_FragPos;
smooth out vec3 g_Normal;
smooth out vec3 g_Tangent;

void main()
{
	vec3 edge0 = v_FragPos[1] - v_FragPos[0];
	vec3 edge1 = v_FragPos[2] - v_FragPos[0];
	vec2 dUV0 = v_TexCoord[1] - v_TexCoord[0];
	vec2 dUV1 = v_TexCoord[2] - v_TexCoord[0];
	
	//calculate surface normal
	g_Normal = normalize(cross(edge0, edge1));
	
	//calculate surface tangent
	float f = 1 / (dUV0.x * dUV1.y - dUV1.x * dUV0.y);
	g_Tangent = normalize(vec3(
			(f*(dUV1.y*edge0.x - dUV0.y*edge1.x)),
			(f*(dUV1.y*edge0.y - dUV0.y*edge1.y)),
			(f*(dUV1.y*edge0.z - dUV0.y*edge1.z))
		));
	
	//pass through the rest of values
    for(int i = 0;i < gl_in.length();i++)
    {
        g_FragPos = v_FragPos[i];
        g_TexCoord = v_TexCoord[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
};