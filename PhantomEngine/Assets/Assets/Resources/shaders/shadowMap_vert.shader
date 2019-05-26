#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 inputPosition;

layout( std140) uniform Light
{
    vec4 lightPos;
	vec4 lightColor;
	vec4 lightDir;
	mat4 lightVP;
} light;


layout( std140) uniform ConstantsPerBatch
{
    mat4 modelMatrix;
} uboBatch;

layout( std140) uniform ConstantsPerFrame
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    vec4 camPos;
} uboFrame;

void main(){
	gl_Position = light.lightVP * uboBatch.modelMatrix * vec4(inputPosition, 1.0f);
}
