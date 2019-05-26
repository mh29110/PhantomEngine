#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 inputPosition;


UNIFORM_BLOCK_MACRO

void main(){
	gl_Position = light.lightVP * uboBatch.modelMatrix * vec4(inputPosition, 1.0f);
}
