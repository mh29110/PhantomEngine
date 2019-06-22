#include "window.h"

namespace Phantom { namespace graphics {

	void windowResize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		// printf("%d\n", xpos);
		// printf("%d\n", ypos);
		//Window* win = (Window*)glfwGetWindowUserPointer(window);
		mouse_x = xpos;
		mouse_y = ypos;
	}

	Window::Window(const char *title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init())
			glfwTerminate();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to Init GLFW!" << std::endl;
			return false;
		}
		//版本号 opengl3.0 (举例)
		// Set up OpenGL options.
		// Use OpenGL verion 4.1,
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		// GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		// Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// Make the window resize-able.
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window!" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetWindowSizeCallback(m_Window, windowResize);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(1);//vAsync  每帧交换一次缓冲器

		// must after  glfwMakeContextCurrent	
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to Init GLAD" << std::endl;
			return false;
		}

		// std::cout << m_Width <<std::endl;
		// windowResize(m_Window, m_Width, m_Height);

		std::cout << glGetString(GL_VERSION) << std::endl;
		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;

	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void Window::terminate() const 
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	

	
} }