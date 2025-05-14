#pragma once

#include <queue>
#include <set>
#include <iostream>
#include <vector>

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
bool is_valid(const CellIndex &cell, const std::vector<std::vector<char>> &map);
void do_bfs(CellIndex start, const std::vector<std::vector<char>> &map);
