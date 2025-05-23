#include "enemies.hpp"

bool is_starting{true};
bool is_ending{false};

void heatmap_with_cell(Map const &map)
{

    std::vector<float> next_mvt{490.f, 490.f};

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

            if (next_mvt[0] < 1.f && next_mvt[1] < 1.f)
            {
                is_ending = true;
            }
        }
    }

    myEngine.mvMatrixStack.pushMatrix();
    Vector3D cell_tr{next_mvt[0], next_mvt[1], 0.f};
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

    std::vector<CellIndex> neighbors{
        {current_x, current_y - 1},
        {current_x + 1, current_y - 1},
        {current_x + 1, current_y},
        {current_x + 1, current_y + 1},
        {current_x, current_y + 1},
        {current_x - 1, current_y + 1},
        {current_x - 1, current_y},
        {current_x - 1, current_y - 1},
    };

    for (int i = 0; i < neighbors.size(); i++)
    {
        if (isValid(neighbors[i], map))
        {
            if (distances[current_x][current_y] > distances[neighbors[i].x][neighbors[i].y])
            {
                next_mvt = {
                    static_cast<float>(neighbors[i].x) * 10.f, static_cast<float>(neighbors[i].y) * 10.f};
            }
        }
    }

    return next_mvt;
}