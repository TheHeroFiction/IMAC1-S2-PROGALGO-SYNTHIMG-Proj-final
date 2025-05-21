#include "key_options.hpp"

using namespace glbasimac;

GLBI_Engine myEngine;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,key);
	}

}
