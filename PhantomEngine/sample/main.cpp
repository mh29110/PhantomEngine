#include "src/maths/maths.h"
#include "src/graphics/shader.h"
#include "src/graphics/window.h"
#include "src/graphics/GVertexArray.h"
#include "src/graphics/GVertexBuffer.h"
#include "src/graphics/GIndexBuffer.h"
#include "src/graphics/renderable.h"
#include "src/graphics/renderer.h"

using namespace phantom::maths;
using namespace phantom;
using namespace graphics;

GLuint m_ShaderID;
double mouse_x = 0.0;
double mouse_y = 0.0;
const char* MVP_NAME_M = "ojbect2world_matrix";
const char* MVP_NAME_V = "world2view_matrix";
const char* MVP_NAME_P = "projection_matrix";



int main()
{
	Window window("phantom!", 960, 540);

	Renderer renderer;
	//osx
    //Shader shader("shaders/vert_light.shader","shaders/frag_light.shader");
	//vs
     Shader shader("Resources/shaders/vert_light.shader","Resources/shaders/frag_light.shader");
    m_ShaderID = shader.m_ShaderId;
    shader.bind();

	Renderable sprite1(vec3(0, 1, 0), vec3(0.3f, 0.3f, 0.3f), shader);
	Renderable sprite2(vec3(3, 1, 0), vec3(0.3f, 0.3f, 0.3f), shader);
	Renderable sprite3(vec3(6, 1, 0), vec3(0.3f, 0.3f, 0.3f), shader);
	Renderable sprite4(vec3(9, 1, 0), vec3(0.3f, 0.3f, 0.3f), shader);
	Renderable sprite5(vec3(12, 1, 0), vec3(0.3f, 0.3f, 0.3f), shader);
	


	mat4x4 proMat(1);
 	proMat.orthographic(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
 	proMat.perspective(90.0f, 16.0f/9.0f, 0.01f, 1000.0f);
	mat4x4 viewMat(1);
	viewMat.LookAtMatrixBuild(vec3(0, 0,2), vec3(0, 0 , 0), vec3(0 ,1, 0));
	std::cout << viewMat << std::endl;

	shader.setUniformMat4(MVP_NAME_V, viewMat);
 	shader.setUniformMat4(MVP_NAME_P, proMat);
 	shader.setUniform2f("light_pos",vec2(4.0f ,1.5f));
 	shader.setUniform4f("color_light",vec4(1.0f,0.7f,0.8f,1.0f));
 	shader.setUniform1f("factor_light", 1.3f);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	GLfloat radius = 10.0f;

	while (!window.closed())
	{
        window.clear();
        glUseProgram(m_ShaderID);

		GLfloat camX = sin(glfwGetTime()) * radius;
		GLfloat camZ = cos(glfwGetTime()) * radius;
		viewMat.LookAtMatrixBuild(vec3(camX, 1.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		std::cout << viewMat << std::endl;

		shader.setUniformMat4(MVP_NAME_V, viewMat);
	    shader.setUniform2f("light_pos", vec2((float)(mouse_x * 1.0f / 960.0f - 0.5f), (float)(0.5f - mouse_y * 1.0f / 540.0f)));

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.submit(&sprite3);
		renderer.submit(&sprite4);
		renderer.submit(&sprite5);
		renderer.flush();

        // Swap the screen buffers
		window.update();
	}

	window.terminate();

	return 0;
} 