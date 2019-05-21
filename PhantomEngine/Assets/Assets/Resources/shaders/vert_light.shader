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

uniform mat4 depthVP;

out vec4 vViewPos;
out vec3 normal;
out vec2 texc;
out vec4 vWorldPos;
out vec4 FragPosLightSpace;

void main()
{
    vWorldPos = uboBatch.modelMatrix * inputPosition;
    vViewPos = uboFrame.viewMatrix * vWorldPos;
    gl_Position = uboFrame.projectionMatrix * vViewPos;

    FragPosLightSpace = depthVP * vWorldPos;


    //--法线需要转换到视图空间中才可以参与光照计算  正交矩阵简化： (M \-1) \t  = M 
    //http://www.songho.ca/opengl/gl_normaltransform.html
    //但是我们现在的平行光是写死在世界坐标系空间下，暂时先用世界坐标吧。
    normal = (  uboBatch.modelMatrix * vec4(inputNormal, 0.0f) ).xyz;

    texc = vec2 (inputUV.x , 1-inputUV.y);
}