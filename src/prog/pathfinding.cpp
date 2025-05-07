#include "pathfinding.hpp"
#include <queue>
#include <set>
#include <iostream>

void do_bfs(CellIndex start)
{
    // Création de la file
    std::queue<CellIndex> cell_queue;
    std::set<CellIndex> visited;

    cell_queue.push(start);
    visited.insert(start);

    // Tant qu'il y a des éléments dans la file, on cherche les cases adjacentes
    while (!cell_queue.empty())
    {
        CellIndex current = cell_queue.front();
        cell_queue.pop();

        std::cout << "Visiting: (" << current.x << ", " << current.y << ")\n";

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
    }
}
