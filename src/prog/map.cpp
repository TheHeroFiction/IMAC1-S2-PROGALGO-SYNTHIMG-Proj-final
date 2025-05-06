#include "map.hpp"

std::vector<std::vector<char>> generate_map(int width, int height)
{
    std::srand(std::time(nullptr));
    std::vector<std::vector<char>> rows {};
    for (int i {0}; i < width; i++)
    {
        std::vector<char> colunm {};
        for ( int j {0}; j < height; j++)
        {
            if ((std::rand() % 100 + 1) < 51)
            {
                colunm.push_back('#'); //ASCII for #
            }
            else
            {
                colunm.push_back(' '); //ASCII for [space]
            }
        }
        rows.push_back(colunm);
    }
    return rows;
}

void print_map(std::vector<std::vector<char>> const& map)
{
    for (int i {0}; i < map.size(); i++)
    {
        for (int j {0}; j < map[i].size(); j++)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}