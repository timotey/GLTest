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

 vec3 u_LightPos = vec3(3);
vec3 u_CameraPos = vec3(0);
material u_Material;
uniform sampler2D u_Tex0;

void main()
{
	
	u_Material.ambient = vec3(0.329412,0.223529,0.027451);
	u_Material.diffuse = vec3(0.780392,0.568627,0.113725);
	u_Material.specular = vec3(0.992157,0.941176,0.807843);
	u_Material.shininess = 0.21794872;
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