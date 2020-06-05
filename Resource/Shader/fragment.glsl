#version 430 core
layout(location = 0) out vec4 col;
layout(location = 1) out vec4 pos;
layout(location = 2) out vec4 norm;
layout (depth_less) out float gl_FragDepth;
smooth in vec3 g_Normal;
smooth in vec3 g_Tangent;
smooth in vec3 g_FragPos;
smooth in vec2 g_TexCoord;

uniform sampler2D u_Tex0;

void main()
{
	vec3 Bitangent = cross(g_Normal, g_Tangent);
	//if(!gl_FrontFacing) discard;
	gl_FragDepth = gl_FragCoord.z;
	
	col = vec4(vec3(texture(u_Tex0, g_TexCoord)),0.5);
	pos = vec4(g_FragPos,1);
	norm = vec4((g_Normal/2)+vec3(0.5),1);
};
