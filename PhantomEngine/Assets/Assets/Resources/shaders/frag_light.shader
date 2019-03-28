#version 410 core

layout (location = 0) out vec4 color;

uniform vec4 color_light;
uniform vec2 light_pos;
uniform float factor_light;
uniform sampler2D diffuseColor;

in vec4 pos;
in vec3 norl;
in vec2 texc;

void main()
{
	//float intensity = factor_light * 1.0 / length(pos.xy - light_pos);
	//color = mcolor * intensity * color_light;
	vec4 diff = texture(diffuseColor, texc.xy);
	color = diff;
} 

