#include <iostream>
#include <GLFW/glfw3.h>
using namespace std;
int main() {
	printf("Hello Engine!\n");
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return 1;
	}

	return 0;
}