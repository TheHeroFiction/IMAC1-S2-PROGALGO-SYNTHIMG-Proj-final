#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

std::vector<std::vector<char>> generate_map(int width, int height);

void print_map(std::vector<std::vector<char>> const& map);