#include "map.hpp"

int main()
{
    std::vector<std::vector<char>> new_map {generate_map(50,50)};
    print_map(new_map);
    return 0;
}