#include "src/graphics/window.h"
#include "src/maths/maths.h"

using namespace phantom::maths;
int main()
{
	using namespace phantom;
	using namespace graphics;

	Window window("phantom!", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);


	GLfloat vertices[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
	GLuint vaoId,vboId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1,&vboId);
	glBindBuffer(GL_ARRAY_BUFFER,vboId);

	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT	,GL_FALSE,3*sizeof(GL_FLOAT),(GLvoid*) 0);
	glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#if( 1 )
	/*mat4x4 m1(  1, 0, 0, 0, 
				0, 1, 0, 0,
				0, 0, 1, 0, 
				5, 0, 0, 1);*/
#endif
#if(0)
	vec2 v1(3,2);
	vec2 v2(1, 3);
	vec2 v3;
	v3 = v2 + v1;
	std::cout << v1 << v2 << v3<<"x="<< std::endl;

	vec4 v4(3,2,0,1);
	vec4 v5(1, 3,100,3);
	vec4 v6;
	v4 = v5+ v6;
	std::cout << v4 << v5 << v6<<std::endl;

	vec2 vv1(1, 0);
	vec2 vv2(1, 1);
	float angle = vv1.getAngle(vv2);
	std::cout << angle << std::endl;

#endif
	while (!window.closed())
	{
		window.clear();
		glColor3f(1.0, 1.0, 1.0);
		glBindVertexArray(vaoId); // 使用VAO信息
    	glDrawArrays(GL_TRIANGLES, 0, 3);
		window.update();
	}
	window.terminate();

	return 0;
} 