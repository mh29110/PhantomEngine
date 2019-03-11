#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 color_light;
uniform vec2 light_pos;
uniform float factor_light;

in vec4 pos;
in vec4 mcolor;

void main()
{
	float intensity = factor_light * 1.0 / length(pos.xy - light_pos);
	color = mcolor * intensity * color_light;
} 