#pragma once
#include "map.hpp"
#include "key_options.hpp"
#include "pathfinding.hpp"
#include "enemies.hpp"
#include "simpletext.h"

enum class GameState
{
    MENU,
    PLAYING
};

extern GameState currentState;
extern float aspectRatio;
extern const float GL_VIEW_SIZE;
// menu.hpp
extern SimpleText *TextRenderer;

void drawMenu();

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);