#include "src/graphics/window.h"
#include "src/maths/maths.h"
using namespace phantom::maths;
int main()
{
	using namespace phantom;
	using namespace graphics;

	Window window("phantom!", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
#if(1)
	vec4 v1(3,2,0,1);
	vec4 v2(1, 3,100,3);
	vec4 v3;
	float x = (v2 * v1);
	std::cout << v1 << v2 << v3<<"x="<<x<< std::endl;

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
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}
	window.terminate();

	return 0;
} 