#include "map.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include <iostream>

using namespace glbasimac;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* OpenGL Engine */
GLBI_Engine myEngine;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

int main() {
    /*
    std::vector<std::vector<char>> new_map {generate_map(50,50)};
    std::cout << " RAW MAP " << std::endl;
    print_map(new_map);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 1ST" << std::endl;
    std::vector<std::vector<char>> map_first_ite {cellular_automata(new_map)};
    print_map(map_first_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 2ND" << std::endl;
    std::vector<std::vector<char>> map_sec_ite {cellular_automata(map_first_ite)};
    print_map(map_sec_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 3RD" << std::endl;
    std::vector<std::vector<char>> map_third_ite {cellular_automata(map_sec_ite)};
    print_map(map_third_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 4TH" << std::endl;
    std::vector<std::vector<char>> map_fourth_ite {cellular_automata(map_third_ite)};
    print_map(map_fourth_ite);
    */

    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1024, 720, "OpenGLTemplate", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	// Initialize Rendering Engine
	myEngine.initGL();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClearColor(0.2f,0.f,0.f,0.f);
		glClear(GL_COLOR_BUFFER_BIT);

        // render here

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}

    glfwTerminate();
    return 0;
}