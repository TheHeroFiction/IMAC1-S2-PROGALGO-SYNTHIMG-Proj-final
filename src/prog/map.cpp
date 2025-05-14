#include "map.hpp"

using namespace glbasimac;

//variables
GLBI_Convex_2D_Shape cell {};
std::vector<std::vector<float>> cells_coords {};
std::vector<std::vector<float>> cells_colors {};

std::vector<float> color_floor {1.f,1.f,1.f, 1.f,1.f,1.f, 1.f,1.f,1.f, 1.f,1.f,1.f};
std::vector<float> color_wall {0.f,0.f,0.f, 0.f,0.f,0.f, 0.f,0.f,0.f, 0.f,0.f,0.f };

//fonctions
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

char map_edge_computing(std::vector<std::vector<char>> const& map, int concerned_edge , int x_coordinate, int y_coordinate)
{
    int full_cell {0};
    switch (concerned_edge)
    {
    case 0: //upper_edge
        if (map[x_coordinate][y_coordinate-1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate+1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate+1][y_coordinate-1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate+1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate+1][y_coordinate+1] == '#')
        {
            full_cell++;
        }
        break;
    case 1: //left_edge
        if (map[x_coordinate-1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate+1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate-1][y_coordinate+1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate+1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate+1][y_coordinate+1] == '#')
        {
            full_cell++;
        }
        break;
    case 2: //right_edge
        if (map[x_coordinate-1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate+1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate-1][y_coordinate-1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate-1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate+1][y_coordinate-1] == '#')
        {
            full_cell++;
        }
        break;
    case 3: //lower_edge
        if (map[x_coordinate][y_coordinate-1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate][y_coordinate+1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate-1][y_coordinate-1] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate-1][y_coordinate] == '#')
        {
            full_cell++;
        }
        if (map[x_coordinate-1][y_coordinate+1] == '#')
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

char map_center_computing(std::vector<std::vector<char>> const& map, int x_coordinate, int y_coordinate)
{
    int full_cell {0};
    if (map[x_coordinate][y_coordinate-1] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate][y_coordinate] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate][y_coordinate+1] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate-1][y_coordinate-1] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate-1][y_coordinate] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate-1][y_coordinate+1] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate+1][y_coordinate-1] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate+1][y_coordinate] == '#')
    {
        full_cell++;
    }
    if (map[x_coordinate+1][y_coordinate+1] == '#')
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

std::vector<std::vector<char>> cellular_automata(std::vector<std::vector<char>> const& map)
{
    std::vector<std::vector<char>> new_map {};
    //left_edge computing
    for (int row {0}; row < map.size(); row++)
    {
        std::vector<char> new_row {};
        if(row == 0 || row == map.size()-1)
        {
            new_row.push_back(' ');
        }
        else
        {
            new_row.push_back(map_edge_computing(map,1,row,0));
        }
        new_map.push_back(new_row);
    }
    //upper_edge & lower_edge computing
    for (int col {1}; col < map.size(); col++ )
    {
        if (col == map.size() -1)
        {
            new_map[0].push_back(' ');
            new_map[map.size()-1].push_back(' ');
        }
        else
        {
            new_map[0].push_back(map_edge_computing(map,0,0,col));
            new_map[map.size()-1].push_back(map_edge_computing(map,3,map.size()-1,col));
        }
    }
    // center computing
    for (int row {1}; row < map.size()-1; row++)
    {
        for (int col {1}; col < map[row].size()-1; col++)
        {
            new_map[row].push_back(map_center_computing(map,row,col));
        }
    }
    //right_edge computing
    for (int row {1}; row < map.size()-1; row++ )
    {
        new_map[row].push_back(map_edge_computing(map,2,row,map.size()-1));
    }
    return new_map;
}

void init_map(std::vector<std::vector<char>> const& map, int width, int height, float view_size)
{
    float cell_width {static_cast<float>(width)/static_cast<float>(map.size())};
    float cell_height {static_cast<float>(height)/static_cast<float>(map[0].size())};

    std::vector<float> coords {};
    
    for (int row {0}; row < map.size(); row++)
    {
        for (int col {0}; col < map[0].size(); col++)
        {
            coords = 
            {
                cell_height * row - view_size/2.f, cell_width * col - view_size/2.f, //high left corner
                cell_height * row - view_size/2.f, cell_width * (col + 1) - view_size/2.f, //high right corner 
                cell_height * (row + 1) - view_size/2.f, cell_width * (col + 1) - view_size/2.f, // low right corner
                cell_height * (row + 1) - view_size/2.f, cell_width * col - view_size/2.f // low left corner
            };

            cells_coords.push_back(coords);
            
            if (map[row][col] == '#')
            {
                cells_colors.push_back(color_wall);
            }
            else
            {
                cells_colors.push_back(color_floor);
            }

            
        }
    }

    cell.initShape({0.f,0.f, 0.f,5.f, 5.f,5.f, 5.f,0.f});
    cell.changeNature(GL_TRIANGLE_FAN);
}

void render_map()
{
    myEngine.setFlatColor(0.5f,0.5f,0.5f);
    cell.drawShape();
    std::cout<< cells_coords[0][0] << ',' << cells_coords[0][1] << std::endl;
}