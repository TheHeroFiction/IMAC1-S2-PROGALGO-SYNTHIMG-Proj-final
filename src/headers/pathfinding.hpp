#pragma once

#include <queue>
#include <set>
#include <iostream>
#include <vector>

// Variables
extern std::vector<std::vector<int>> distances;

// enum class Direction
// {
//     None,
//     Up,
//     Down,
//     Left,
//     Right
// };

// struct DirOffset
// {
//     int dx, dy;
//     Direction dir;
// };

// const DirOffset directions[4] = {
//     {0, -1, Direction::Up},
//     {0, 1, Direction::Down},
//     {-1, 0, Direction::Left},
//     {1, 0, Direction::Right}};

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
bool isValid(const CellIndex &cell, const std::vector<std::vector<char>> &map);
void doBFS(CellIndex start, const std::vector<std::vector<char>> &map);
