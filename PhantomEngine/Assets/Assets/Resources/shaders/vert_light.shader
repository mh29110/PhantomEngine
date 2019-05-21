#version 410 core

layout(location = 0) in vec4 inputPosition;
layout(location = 1) in vec3 inputNormal;
layout(location = 2) in vec2 inputUV;


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
out vec3 normal;
out vec2 texc;
out vec4 v_world;

void main()
{

    gl_Position = uboFrame.projectionMatrix * uboFrame.viewMatrix *  uboBatch.modelMatrix * inputPosition;
    pos = uboBatch.modelMatrix * inputPosition;
    v_world = gl_Position;


    //--法线需要转换到视图空间中才可以参与光照计算
    //http://www.songho.ca/opengl/gl_normaltransform.html
    normal = ( uboFrame.viewMatrix *  uboBatch.modelMatrix * vec4(inputNormal, 0.0f) ).xyz;

    texc = vec2 (inputUV.x , 1-inputUV.y);
}