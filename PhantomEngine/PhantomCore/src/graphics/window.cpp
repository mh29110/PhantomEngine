#include "window.h"

namespace phantom { namespace graphics {

	static void windowResize(GLFWwindow *window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		//版本号 opengl3.0 (举例)
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window!" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwSetKeyCallback(m_Window, key_callback);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowSizeCallback(m_Window, windowResize);
		glfwSwapInterval(1);

		// must after  glfwMakeContextCurrent	
		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialize glew!" << std::endl;
			glfwTerminate();
			return false;
		}

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

	void windowResize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
    	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	    glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
} }