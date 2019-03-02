#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;


void main()
{
	color = colour ;
	color = vec4(1.0f ,0.0f ,0.0f ,1.0f) ;
} 