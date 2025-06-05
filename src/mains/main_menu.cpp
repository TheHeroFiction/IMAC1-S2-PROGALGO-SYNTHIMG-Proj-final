#include "menu.hpp"

using namespace glbasimac;

Map new_map{generate_map(50, 50)};
Map map_first_ite{cellular_automata(new_map)};
Map map_sec_ite{cellular_automata(map_first_ite)};
Map map_third_ite{cellular_automata(map_sec_ite)};
Map map_fourth_ite{cellular_automata(map_third_ite)};

int windowWidth{500};
int windowHeight{500};

GameState currentState = GameState::MENU;

/* Espace virtuel */
const float GL_VIEW_SIZE = 500.f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
float aspectRatio = 1.0f;

/* Error handling function */
void onError(int error, const char *description)
{
    std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow *window, int width, int height)
{
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);
    if (aspectRatio > 1.0)
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio / 2.,
                                 GL_VIEW_SIZE * aspectRatio / 2.,
                                 -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
                                 -GL_VIEW_SIZE / (2. * aspectRatio),
                                 GL_VIEW_SIZE / (2. * aspectRatio));
    }
}

int main()
{

    doBFS({0, 0}, map_fourth_ite);

    // Initialize the library
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Map", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, onWindowResized);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    TextRenderer = new SimpleText{};

    myEngine.initGL();

    // Initialize Rendering Engine
    init_map(map_fourth_ite, windowWidth, windowHeight, GL_VIEW_SIZE);

    onWindowResized(window, windowWidth, windowHeight);

    glfwSetKeyCallback(window, key_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        myEngine.switchToFlatShading();

        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Start at menu */
        if (currentState == GameState::MENU)
        {
            drawMenu();
        }
        else if (currentState == GameState::PLAYING)
        {
            glClearColor(0.2f, 0.f, 0.f, 0.f);
            glClear(GL_COLOR_BUFFER_BIT);

            heatmap_with_cell(map_fourth_ite);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        while (elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
            elapsedTime = glfwGetTime() - startTime;
        }
    }

    glfwTerminate();
    return 0;
}