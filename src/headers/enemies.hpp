#pragma once
#include "map.hpp"
#include "key_options.hpp"
#include "pathfinding.hpp"

void heatmap_with_cell(Map const &map);

std::vector<float> enemy_mvt(float x, float y, Map const &map);