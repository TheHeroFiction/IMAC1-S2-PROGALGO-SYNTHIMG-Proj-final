#include "key_options.hpp"

using namespace glbasimac;

GLBI_Engine myEngine;

// Declare currentState with the correct type
GameState currentState = GameState::MENU;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, key);
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		currentState = GameState::PLAYING;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		currentState = GameState::PAUSE;
	}
}
