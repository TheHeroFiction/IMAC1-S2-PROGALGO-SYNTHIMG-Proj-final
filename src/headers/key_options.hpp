#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"


using namespace glbasimac;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);