#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;


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

out vec4 pos;
out vec3 norl;
out vec2 texc;

void main()
{
    gl_Position = uboFrame.projectionMatrix * uboFrame.viewMatrix *  uboBatch.modelMatrix * position;
    pos = uboBatch.modelMatrix * position;
    texc = texcoord;
    norl = normal;
}