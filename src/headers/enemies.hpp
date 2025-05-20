#pragma once
#include "map.hpp"
#include "key_options.hpp"
#include "pathfinding.hpp"

std::vector<float> enemy_mvt(float x, float y, std::vector<std::vector<char>> const &map);