#include "map.hpp"
#include "pathfinding.hpp"
#include "player.hpp"

using namespace glbasimac;

// variables
GLBI_Convex_2D_Shape cell{};
std::vector<std::vector<float>> cells_coords{};
std::vector<std::vector<float>> cells_colors{};
std::vector<float> color_floor{1.f, 1.f, 1.f};
std::vector<float> color_wall{0.f, 0.f, 0.f};

// fonctions
Map generate_map(int width, int height)
{
    std::srand(std::time(nullptr));
    Map rows{};
    for (int i{0}; i < width; i++)
    {
        std::vector<char> colunm{};
        for (int j{0}; j < height; j++)
        {
            if ((std::rand() % 100 + 1) < 51)
            {
                colunm.push_back('#'); // ASCII for #
            }
            else
            {
                colunm.push_back(' '); // ASCII for [space]
            }
        }
        rows.content.push_back(colunm);
    }
    return rows;
}

void print_map(Map const &map)
{
    for (int i{0}; i < map.content.size(); i++)
    {
        for (int j{0}; j < map.content[i].size(); j++)
        {
            std::cout << map.content[i][j];
        }
        std::cout << std::endl;
    }
}

char map_edge_computing(Map const &map, int concerned_edge, int x_coordinate, int y_coordinate)
{
    int full_cell{0};
    switch (concerned_edge)
    {
    case 0: // upper_edge
        if (map.content[x_coordinate][y_coordinate - 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate + 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate + 1][y_coordinate - 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate + 1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate + 1][y_coordinate + 1] == '#')
        {
            full_cell++;
        }
        break;
    case 1: // left_edge
        if (map.content[x_coordinate - 1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate + 1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate - 1][y_coordinate + 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate + 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate + 1][y_coordinate + 1] == '#')
        {
            full_cell++;
        }
        break;
    case 2: // right_edge
        if (map.content[x_coordinate - 1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate + 1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate - 1][y_coordinate - 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate - 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate + 1][y_coordinate - 1] == '#')
        {
            full_cell++;
        }
        break;
    case 3: // lower_edge
        if (map.content[x_coordinate][y_coordinate - 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate][y_coordinate + 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate - 1][y_coordinate - 1] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate - 1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map.content[x_coordinate - 1][y_coordinate + 1] == '#')
        {
            full_cell++;
        }
        break;
    default:
        break;
    }

    if (full_cell > 4)
    {
        return '#';
    }
    else
    {
        return ' ';
    }
}

char map_center_computing(Map const &map, int x_coordinate, int y_coordinate)
{
    int full_cell{0};
    if (map.content[x_coordinate][y_coordinate - 1] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate][y_coordinate] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate][y_coordinate + 1] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate - 1][y_coordinate - 1] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate - 1][y_coordinate] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate - 1][y_coordinate + 1] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate + 1][y_coordinate - 1] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate + 1][y_coordinate] == '#')
    {
        full_cell++;
    }
    if (map.content[x_coordinate + 1][y_coordinate + 1] == '#')
    {
        full_cell++;
    }

    if (full_cell > 4)
    {
        return '#';
    }
    else
    {
        return ' ';
    }
}

Map cellular_automata(Map const &map)
{
    Map new_map{};
    // left_edge computing
    for (int row{0}; row < map.content.size(); row++)
    {
        std::vector<char> new_row{};
        if (row == 0 || row == map.content.size() - 1)
        {
            new_row.push_back(' ');
        }
        else
        {
            new_row.push_back(map_edge_computing(map, 1, row, 0));
        }
        new_map.content.push_back(new_row);
    }
    // upper_edge & lower_edge computing
    for (int col{1}; col < map.content.size(); col++)
    {
        if (col == map.content.size() - 1)
        {
            new_map.content[0].push_back(' ');
            new_map.content[map.content.size() - 1].push_back(' ');
        }
        else
        {
            new_map.content[0].push_back(map_edge_computing(map, 0, 0, col));
            new_map.content[map.content.size() - 1].push_back(map_edge_computing(map, 3, map.content.size() - 1, col));
        }
    }
    // center computing
    for (int row{1}; row < map.content.size() - 1; row++)
    {
        for (int col{1}; col < map.content[row].size() - 1; col++)
        {
            new_map.content[row].push_back(map_center_computing(map, row, col));
        }
    }
    // right_edge computing
    for (int row{1}; row < map.content.size() - 1; row++)
    {
        new_map.content[row].push_back(map_edge_computing(map, 2, row, map.content.size() - 1));
    }
    return new_map;
}

void init_map(Map const &map, int width, int height, float view_size)
{
    float cell_width{static_cast<float>(width) / static_cast<float>(map.content.size())};
    float cell_height{static_cast<float>(height) / static_cast<float>(map.content[0].size())};

    std::vector<float> coords{};

    for (int row{0}; row < map.content.size(); row++)
    {
        for (int col{0}; col < map.content[0].size(); col++)
        {
            coords =
                {
                    cell_height * col - view_size / 2.f, -(cell_width * row - view_size / 2.f),             // high left corner
                    cell_height * col - view_size / 2.f, -(cell_width * (row + 1) - view_size / 2.f),       // high right corner
                    cell_height * (col + 1) - view_size / 2.f, -(cell_width * (row + 1) - view_size / 2.f), // low right corner
                    cell_height * (col + 1) - view_size / 2.f, -(cell_width * row - view_size / 2.f)        // low left corner
                };

            cells_coords.push_back(coords);

            if (map.content[row][col] == '#')
            {
                cells_colors.push_back(color_wall);
            }
            else
            {
                cells_colors.push_back(color_floor);
            }
        }
    }

    cell.initShape(cells_coords[0]);
    cell.changeNature(GL_TRIANGLE_FAN);
}

void render_map()
{
    int count{0};
    for (int row{0}; row < 50; row++)
    {
        for (int col{0}; col < 50; col++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            Vector3D tr{0.f + 10.f * col, 0.f - 10.f * row, 0.f};
            myEngine.mvMatrixStack.addTranslation(tr);
            myEngine.updateMvMatrix();
            if (player.current_stage.content[row][col] == '#')
            {
                myEngine.setFlatColor(0.f, 0.f, 0.f);
            }
            else
            {
                myEngine.setFlatColor(1.f, 1.f,1.f);
            }
            cell.drawShape();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
            count++;
        }
    }
}

void render_heat_map()
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
}