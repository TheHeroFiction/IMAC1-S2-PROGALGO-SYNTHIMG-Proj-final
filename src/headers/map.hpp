#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "key_options.hpp"

std::vector<std::vector<char>> generate_map(int width, int height);

void print_map(std::vector<std::vector<char>> const& map);

char map_edge_computing(std::vector<std::vector<char>> const& map, int concerned_edge , int x_coordinate, int y_coordinate);

std::vector<std::vector<char>> cellular_automata(std::vector<std::vector<char>> const& map);

void init_map(std::vector<std::vector<char>> const& map, int width, int height, float view_size);

void render_map();