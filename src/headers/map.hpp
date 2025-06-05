#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "key_options.hpp"


struct Map
{
    std::vector<std::vector<char>> content;
};

extern GLBI_Convex_2D_Shape cell;

Map generate_map(int width, int height);

void print_map(Map const &map);

char map_edge_computing(Map const &map, int concerned_edge, int x_coordinate, int y_coordinate);

Map cellular_automata(Map const &map);

void init_map(Map const &map, int width, int height, float view_size);

void render_map();

void render_heat_map();

Map generate_special_items_map(Map const& map);

