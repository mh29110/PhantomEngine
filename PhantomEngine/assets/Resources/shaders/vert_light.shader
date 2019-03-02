#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 projection_matrix;
uniform mat4 ojbect2world_matrix = mat(1.0);
uniform mat4 world2view_matrix = mat(1.0);

out vec4 pos;

void main()
{
    gl_position = projection_matrix * world2view_matrix * ojbect2world_matrix * position;
    pos = ojbect2world_matrix * position;
}