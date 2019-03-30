#version 410 core

layout (location = 0) out vec4 color;

layout( std140) uniform Light
{
    vec4 lightPos;
	vec4 lightColor;
	vec4 lightDir;
} light;

uniform sampler2D diffuseColor;

in vec4 pos;
in vec3 norl;
in vec2 texc;

void main()
{
	vec4 diff = texture(diffuseColor, texc.xy);

	vec3 norm = normalize(norl);
	vec3 dir = normalize(light.lightDir.xyz);
	float diffFactor = max(dot(norm, dir), 0.0);
	vec4 diffuse = diffFactor * light.lightColor;

	color = diff * diffuse;
} 

