#version 430 core
out vec4 color;
smooth in vec2 texCoord;


const float offset = 0;

uniform sampler2D u_norm;
uniform sampler2D u_pos;
uniform sampler2D u_alb;
uniform samplerCube u_c;
uniform mat4 u_V;
void main()
{
	vec3 texnorm = vec3(texture(u_norm, texCoord));
	vec3 norm = texnorm != 0 ? normalize((texnorm-vec3(0.5))*2): vec3(0);
	vec4 alb = texture(u_alb, texCoord);
	if(norm == vec3(0))
		discard;
	vec3 pos = vec3(texture(u_pos, texCoord));
	vec3 reflectdir = vec3(vec4(reflect(pos.xyz, norm.xyz), 1) * u_V);
	color = vec4(mix(alb.xyz, texture(u_c,reflectdir).xyz, alb.w),1);
	//color = vec4(alb.xyz,1);
};
