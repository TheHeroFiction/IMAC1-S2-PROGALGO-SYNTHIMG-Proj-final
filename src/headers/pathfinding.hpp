#pragma once

#include <queue>
#include <set>
#include <iostream>
#include <vector>

#include "map.hpp"

// Variables
extern std::vector<std::vector<int>> distances;

struct CellIndex
{
    int x;
    int y;

    bool operator<(const CellIndex &other) const
    {
        return x == other.x ? y < other.y : x < other.x;
    }

    bool operator==(const CellIndex &other) const
    {
        return x == other.x && y == other.y;
    }
};

unsigned int distance(CellIndex start_cell, CellIndex current_cell);
bool isValid(const CellIndex &cell, const Map &map);
bool isWall(const CellIndex &cell, const Map &map);
void doBFS(CellIndex start, const Map &map);
