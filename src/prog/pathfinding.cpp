#include "pathfinding.hpp"

unsigned int distance(CellIndex start_cell, CellIndex current_cell)
{
    unsigned int distance_x{};
    unsigned int distance_y{};

    if (start_cell.x < current_cell.x)
    {
        distance_x = current_cell.x - start_cell.x;
    }
    else
    {
        distance_x = start_cell.x - current_cell.x;
    }

    if (start_cell.y < current_cell.y)
    {
        distance_y = current_cell.y - start_cell.y;
    }
    else
    {
        distance_y = start_cell.y - current_cell.y;
    }

    return distance_x + distance_y;
}

void do_bfs(CellIndex start, std::vector<std::vector<char>> map)
{
    // Création de la file
    std::queue<CellIndex> cell_queue;
    std::set<CellIndex> visited;

    cell_queue.push(start);
    visited.insert(start);

    int counter{};
    size_t counter_map{};
    size_t map_size{map.size() * map[0].size()};

    // Tant qu'il y a des éléments dans la file, on cherche les cases adjacentes
    while (!cell_queue.empty() && counter_map < map_size)
    {
        // if (counter == 8)
        // {
        //     break;
        // }

        CellIndex current = cell_queue.front();
        cell_queue.pop();

        std::cout << "Visiting: (" << current.x << ", " << current.y << ")\n";

        std::cout << "Distance :" << distance(start, current) << std::endl;

        // Les 4 voisins adjacents
        CellIndex neighbors[4] = {
            {current.x + 1, current.y},
            {current.x - 1, current.y},
            {current.x, current.y + 1},
            {current.x, current.y - 1}};

        for (auto &neighbor : neighbors)
        {
            // Exemple de condition pour éviter d'aller dans des coordonnées négatives
            // On évite aussi les effets de bord
            if (neighbor.x >= 0 && neighbor.y >= 0 && visited.find(neighbor) == visited.end() && neighbor.x < map.size() && neighbor.y < map[0].size())
            {
                visited.insert(neighbor);
                cell_queue.push(neighbor);
            }
        }

        counter_map++;
        // counter++;
    }

    std::cout << "Visited size: " << visited.size() << "\n";
    std::cout << map_size << "\n";
    std::cout << counter_map << "\n";
}
