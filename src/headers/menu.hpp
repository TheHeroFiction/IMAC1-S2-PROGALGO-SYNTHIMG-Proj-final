#pragma once
#include "map.hpp"
#include "key_options.hpp"
#include "pathfinding.hpp"
#include "enemies.hpp"
#include "simpletext.h"

extern float aspectRatio;
extern const float GL_VIEW_SIZE;
extern SimpleText *TextRenderer;

void drawMenu();
void drawWin(const int &score, const int &time);
void drawLose();
void drawPause();
void drawUI(const int &score, const int &time);