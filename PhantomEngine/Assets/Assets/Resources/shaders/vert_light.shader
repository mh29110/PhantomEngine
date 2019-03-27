#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 datacolor;


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
out vec4 mcolor;

void main()
{
    gl_Position = uboFrame.projectionMatrix * uboFrame.viewMatrix *  uboBatch.modelMatrix * position;
    pos = uboBatch.modelMatrix * position;
    mcolor = datacolor;
}