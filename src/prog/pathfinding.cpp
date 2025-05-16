#include "pathfinding.hpp"

// Vérifie si une position est valide sur la carte
// La cell est-elle dans la map (donc supérieur ou égale à 0, inférieur à la longueur et largeur de la map, éviter les effets de bords)?
// La cell n'est pas un mur '#'
bool isValid(const CellIndex &cell, const std::vector<std::vector<char>> &map)
{
    int height = map.size();
    int width = map[0].size();

    return cell.x >= 0 && cell.y >= 0 &&
           cell.x < width && cell.y < height &&
           map[cell.y][cell.x] != '#'; // '#' = obstacle/mur
}

void doBFS(CellIndex start, const std::vector<std::vector<char>> &map)
{
    // Création de la file
    std::queue<CellIndex> cell_queue;
    std::set<CellIndex> visited;

    // Grille de distances et Grille de directions
    std::vector<std::vector<int>> distance_map(map.size(), std::vector<int>(map[0].size(), -1));
    // std::vector<std::vector<Direction>> direction_map(
    //     map.size(),
    //     std::vector<Direction>(map[0].size(), Direction::None));

    cell_queue.push(start);
    visited.insert(start);
    distance_map[start.y][start.x] = 0; // Distance du départ à lui-même

    int counter{};
    size_t counter_map{};
    size_t map_size{map.size() * map[0].size()};

    // Tant qu'il y a des éléments dans la file, on cherche les cases adjacentes
    while (!cell_queue.empty() && counter_map < map_size)
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
            if (isValid(neighbor, map) && visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                distance_map[neighbor.y][neighbor.x] = distance_map[current.y][current.x] + 1;
                cell_queue.push(neighbor);
            }
        }

        std::cout << "Distance: " << distance_map[current.y][current.x] << std::endl;
        counter_map++;
    }

    std::cout << "Visited size: " << visited.size() << "\n";
    std::cout << map_size << "\n";
    std::cout << counter_map << "\n";
}
