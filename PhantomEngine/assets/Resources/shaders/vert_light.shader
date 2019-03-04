#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 datacolor;

uniform mat4 projection_matrix;
uniform mat4 ojbect2world_matrix = mat4(1.0);
uniform mat4 world2view_matrix = mat4(1.0);

out vec4 pos;
out vec4 mcolor;

void main()
{
    gl_Position = projection_matrix * world2view_matrix * ojbect2world_matrix * position;
    pos = ojbect2world_matrix * position;
    mcolor = datacolor;
}