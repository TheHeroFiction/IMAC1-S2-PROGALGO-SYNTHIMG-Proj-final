#include "map.hpp"

int main()
{
    std::vector<std::vector<char>> new_map {generate_map(50,50)};
    std::cout << " RAW MAP " << std::endl;
    print_map(new_map);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 1ST" << std::endl;
    std::vector<std::vector<char>> map_first_ite {cellular_automata(new_map)};
    print_map(map_first_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 2ND" << std::endl;
    std::vector<std::vector<char>> map_sec_ite {cellular_automata(map_first_ite)};
    print_map(map_sec_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 3RD" << std::endl;
    std::vector<std::vector<char>> map_third_ite {cellular_automata(map_sec_ite)};
    print_map(map_third_ite);
    std::cout << std::endl;
    std::cout << " MAP CELLULAR AUTOMATA 4TH" << std::endl;
    std::vector<std::vector<char>> map_fourth_ite {cellular_automata(map_third_ite)};
    print_map(map_fourth_ite);
    return 0;
}