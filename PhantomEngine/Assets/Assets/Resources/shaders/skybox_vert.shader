#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

layout( std140) uniform ConstantsPerFrame
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    vec4 camPos;
} uboFrame;


void main()
{
    TexCoords = aPos;
    mat4 _matrix = uboFrame.viewMatrix;
    _matrix[3].x = 0.0;
    _matrix[3].y = 0.0;
    _matrix[3].z = 0.0;
    vec4 pos = uboFrame.projectionMatrix * _matrix * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  