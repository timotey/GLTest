#version 430 core
layout(location = 0) out vec4 color;
layout (depth_less) out float gl_FragDepth;
smooth in vec3 g_Normal;
smooth in vec3 g_FragPos;
smooth in vec2 g_TexCoord;

struct material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;
uniform material u_Material;
uniform sampler2D u_Tex0;

void main()
{
	
	//if(!gl_FrontFacing) discard;
	gl_FragDepth = gl_FragCoord.z;
	
	vec4 defTexColor = texture(u_Tex0, g_TexCoord);
	
	vec3 LightDir = normalize(u_LightPos - g_FragPos);
	vec3 ViewDir = normalize(u_CameraPos - g_FragPos);
	vec3 HalfwayDir = normalize(LightDir + ViewDir);
	vec3 ReflectDir = reflect(-LightDir, g_Normal);
	
	vec3 ambient  = vec3(1.0) * u_Material.ambient;
		vec3 specular = vec3(1.0) * u_Material.specular * pow(max(dot(g_Normal, HalfwayDir), 0.0), u_Material.shininess*4);
	vec3 diffuse  = vec3(1.0) * u_Material.diffuse * max(dot(LightDir, g_Normal), 0.0);
	color = defTexColor * vec4(diffuse+ambient+specular, 1.0f);
};