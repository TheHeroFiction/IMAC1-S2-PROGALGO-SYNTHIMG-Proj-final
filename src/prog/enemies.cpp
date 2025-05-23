#include "enemies.hpp"

bool is_starting{true};
bool is_ending{false};

std::vector<float> next_mvt{490.f, 490.f};

void heatmap_with_cell(Map const &map)
{

    for (int col{0}; col < 50; col++)
    {
        for (int row{0}; row < 50; row++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            Vector3D tr{0.f + 10.f * row, 0.f - 10.f * col, 0.f};
            myEngine.mvMatrixStack.addTranslation(tr);
            myEngine.updateMvMatrix();
            myEngine.setFlatColor(1.f - 0.02f * distances[row][col], 0.01f * distances[row][col], 0.01f * distances[row][col]);
            cell.drawShape();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
    }

    if (is_starting)
    {
        is_starting = false;
    }
    else
    {
        if (!is_ending)
        {
            next_mvt = enemy_mvt(next_mvt[0], next_mvt[1], map);
            std::cout << "Next mvt: " << next_mvt[0] << "," << next_mvt[1] << std::endl;

            if (next_mvt[0] < 1.f && next_mvt[1] < 1.f)
            {
                is_ending = true;
            }
        }
    }

    myEngine.mvMatrixStack.pushMatrix();
    Vector3D cell_tr{next_mvt[0], -next_mvt[1], 0.f};
    myEngine.mvMatrixStack.addTranslation(cell_tr);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    cell.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

std::vector<float> enemy_mvt(float x, float y, Map const &map)
{
    int current_x{static_cast<int>(x) / 10};
    int current_y{static_cast<int>(y) / 10};
    int current_dist{distances[current_x][current_y]};

    std::vector<float> next_mvt{};

    // std::vector<CellIndex> neighbors{
    //     {current_x, current_y - 1},
    //     {current_x + 1, current_y - 1},
    //     {current_x + 1, current_y},
    //     {current_x + 1, current_y + 1},
    //     {current_x, current_y + 1},
    //     {current_x - 1, current_y + 1},
    //     {current_x - 1, current_y},
    //     {current_x - 1, current_y - 1},
    // };
    std::vector<CellIndex> neighbors = {
        {current_x + 1, current_y},
        {current_x - 1, current_y},
        {current_x, current_y + 1},
        {current_x, current_y - 1}};

    int min_dist = current_dist;
    std::cout << "Current: " << min_dist << std::endl;

    std::vector<float> best_mvt = {x, y}; // Par défaut, rester sur place

    int counter_neighbor{};

    for (const auto &neighbor : neighbors)
    {
        if (isValid(neighbor, map) || isWall(neighbor, map))
        {
            counter_neighbor++;
            int neighbor_dist = distances[neighbor.x][neighbor.y];
            std::cout << "Neighbor: " << neighbor_dist << std::endl;
            if (neighbor_dist < min_dist)
            {
                min_dist = neighbor_dist;
                best_mvt = {
                    static_cast<float>(neighbor.x) * 10.f,
                    static_cast<float>(neighbor.y) * 10.f};
            }
        }
    }

    std::cout << "counter :" << counter_neighbor << std::endl;
    counter_neighbor = 0;

    return best_mvt;
}