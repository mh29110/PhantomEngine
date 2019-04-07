#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

//layout( std140) uniform ConstantsPerFrame
//{
//    mat4 viewMatrix;
//    mat4 projectionMatrix;
//    vec4 camPos;
//} uboFrame;


uniform mat4 projection;
uniform mat4 view;

void main()
{
	mat4 _matrix = view;
	_matrix[3].x = 0.0;
    _matrix[3].y = 0.0;
    _matrix[3].z = 0.0;

    TexCoords = aPos;
    vec4 pos = _matrix*vec4(aPos, 1.0f);
    gl_Position = pos.xyww;
}