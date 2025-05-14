#include "pathfinding.hpp"
#include <queue>
#include <set>
#include <iostream>

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

void do_bfs(CellIndex start)
{
    // Création de la file
    std::queue<CellIndex> cell_queue;
    std::set<CellIndex> visited;

    cell_queue.push(start);
    visited.insert(start);

    int counter{};

    // Tant qu'il y a des éléments dans la file, on cherche les cases adjacentes
    while (!cell_queue.empty())
    {
        if (counter == 8)
        {
            break;
        }

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
            if (neighbor.x >= 0 && neighbor.y >= 0 && visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                cell_queue.push(neighbor);
            }
        }

        counter++;
    }

    std::cout << "Visited size: " << visited.size() << "\n";
}
