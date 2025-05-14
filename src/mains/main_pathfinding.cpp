#include "pathfinding.hpp"
#include "map.hpp"

int main()
{
    std::vector<std::vector<char>> new_map{generate_map(50, 50)};

    CellIndex start = {5, 5};
    do_bfs(start, new_map);
    return 0;
}