#include "map.hpp"
#include "key_options.hpp"

using namespace glbasimac;

std::vector<std::vector<char>> new_map {generate_map(50,50)};
std::vector<std::vector<char>> map_first_ite {cellular_automata(new_map)};
std::vector<std::vector<char>> map_sec_ite {cellular_automata(map_first_ite)};
std::vector<std::vector<char>> map_third_ite {cellular_automata(map_sec_ite)};
std::vector<std::vector<char>> map_fourth_ite {cellular_automata(map_third_ite)};

int width {500};
int height {500};

/* Espace virtuel */
static const float GL_VIEW_SIZE = 500.f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;


/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;
	glViewport(0, 0, width, height);
	if( aspectRatio > 1.0)
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2.,
		GL_VIEW_SIZE * aspectRatio / 2. ,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / (2. * aspectRatio), 
		GL_VIEW_SIZE / (2. * aspectRatio));
	}
}


int main() {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, "Map", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window,onWindowResized);

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	// Initialize Rendering Engine
	init_map(new_map, width, height, GL_VIEW_SIZE);

    glfwSetKeyCallback(window, key_callback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClearColor(0.2f,0.f,0.f,0.f);
		glClear(GL_COLOR_BUFFER_BIT);

        // render here
        render_map();

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

    std::cout << " RAW MAP " << std::endl;
    print_map(new_map);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 1ST" << std::endl;
    print_map(map_first_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 2ND" << std::endl;
    print_map(map_sec_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 3RD" << std::endl;
    print_map(map_third_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 4TH" << std::endl;
    print_map(map_fourth_ite);

    glfwTerminate();
    return 0;
}