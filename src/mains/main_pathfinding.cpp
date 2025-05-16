#include "pathfinding.hpp"
// #include "map.hpp"

int main()
{
    // std::vector<std::vector<char>> new_map{generate_map(50, 50)};

    std::vector<std::vector<char>> map = {
        {'.', '.', '.', '.', '.'},
        {'.', '#', '#', '.', '.'},
        {'.', '.', '.', '#', '.'},
        {'.', '#', '.', '.', '.'},
        {'.', '.', '.', '.', '.'}};

    CellIndex start = {2, 2};
    doBFS(start, map);
    return 0;
}