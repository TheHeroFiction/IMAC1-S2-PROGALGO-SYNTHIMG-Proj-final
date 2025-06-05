#include "player.hpp"

Player player {init_player(0.f,0.f)};

void key_callback_player(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    // update _keysState
    if (key >= 0 && key < player.keys_state.size()) 
    {
        player.keys_state[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
    }

    if (key == GLFW_KEY_U && action == GLFW_PRESS)
	{
		player.destroy_block();
	}

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,key);
	}

    
}

Player init_player(float start_coord_x, float start_coord_y)
{
    Player new_player { start_coord_x, start_coord_y};
    for (int i {0}; i < 91; i++)
    {
        new_player.keys_state.push_back(false);
    }
    return new_player;
}

std::vector<float> player_collision_handler(std::vector<float> const& current_pos,std::vector<float> & next_pos, Map & map,std::vector<bool> keys_state)
{
    float facteur {0.1f};
    std::vector<std::vector<float>> new_corners 
    {
        {next_pos[0] + facteur, next_pos[1]} , // upper_left
        {next_pos[0] + 1.f, next_pos[1] - facteur}, //upper_right
        {next_pos[0] + 1.f - facteur, next_pos[1] - 1.f} , //lower_right
        {next_pos[0] , next_pos[1] - 1.f + facteur}  //lower_left
    };

    std::vector<std::vector<int>> corner_in_cell{};
    std::vector<bool> is_gonna_encounter_wall { false, false, false, false};
    bool is_border {false};

    //calculate currents corners of our player
    for (int i {0}; i < new_corners.size(); i++)
    {   
        corner_in_cell.push_back({static_cast<int>(new_corners[i][0]), static_cast<int>(new_corners[i][1])}); 
    }

    if (keys_state[GLFW_KEY_W]) 
    {
        //Look for walls above player
        if (map.content[(-corner_in_cell[0][1])][corner_in_cell[0][0]] == '#')
        {
            is_gonna_encounter_wall[0] = true;
        }
        else
        {
            is_gonna_encounter_wall[0] = false;
        }
        if (map.content[(-corner_in_cell[1][1])][corner_in_cell[1][0]] == '#')
        {
            is_gonna_encounter_wall[1] = true;
        }
        else
        {
            is_gonna_encounter_wall[1] = false;
        }

        if (is_gonna_encounter_wall[0])
        {
            next_pos[0] = current_pos[0];
            next_pos[1] = (corner_in_cell[0][1]-1) * 1.f;
        }
        /*
        if (is_gonna_encounter_wall[1])
        {
            next_pos[0] = current_pos[0];
            next_pos[1] = (corner_in_cell[1][1]-1) * 1.f;
        }
        */
    }
    if (keys_state[GLFW_KEY_S]) 
    {
        //Look for walls under player
        if (map.content[(-corner_in_cell[2][1])][corner_in_cell[2][0]] == '#')
        {
            is_gonna_encounter_wall[2] = true;
        }
        else
        {
            is_gonna_encounter_wall[2] = false;
        }
        if (map.content[(-corner_in_cell[3][1])][corner_in_cell[3][0]] == '#')
        {
            is_gonna_encounter_wall[3] = true;
        }
        else
        {
            is_gonna_encounter_wall[3] = false;
        }

        if (is_gonna_encounter_wall[2])
        {
            next_pos[0] = current_pos[0];
            next_pos[1] = (corner_in_cell[2][1]+1) * 1.f;
        }
        /*
        if (is_gonna_encounter_wall[3])
        {
            next_pos[0] = current_pos[0];
            next_pos[1] = (corner_in_cell[3][1]+1) * 1.f;
        }
        */
    }
    if (keys_state[GLFW_KEY_A]) 
    {
        //Look for walls to the left of player
        if (map.content[(-corner_in_cell[0][1])][corner_in_cell[0][0]] == '#')
        {
            is_gonna_encounter_wall[0] = true;
        }
        else
        {
            is_gonna_encounter_wall[0] = false;
        }
        if (map.content[(-corner_in_cell[3][1])][corner_in_cell[3][0]] == '#')
        {
            is_gonna_encounter_wall[3] = true;
        }
        else
        {
            is_gonna_encounter_wall[3] = false;
        }
        /*
        if (is_gonna_encounter_wall[0])
        {
            next_pos[0] = (corner_in_cell[0][0]+1) * 1.f;
            next_pos[1] =  current_pos[1];
        }
        */
        if (is_gonna_encounter_wall[3])
        {
            next_pos[0] = (corner_in_cell[3][0]+1) * 1.f;
            next_pos[1] =  current_pos[1];
        }
    }
    if (keys_state[GLFW_KEY_D]) 
        {
            //Look for walls to the right of player
            if (map.content[(-corner_in_cell[2][1])][corner_in_cell[2][0]] == '#')
            {
                is_gonna_encounter_wall[2] = true;
            }
            else
            {
                is_gonna_encounter_wall[2] = false;
            }
            if (map.content[(-corner_in_cell[1][1])][corner_in_cell[1][0]] == '#')
            {
                is_gonna_encounter_wall[1] = true;
            }
            else
            {
                is_gonna_encounter_wall[1] = false;
            }
            /*
            if (is_gonna_encounter_wall[2])
            {
                next_pos[0] = (corner_in_cell[2][0]-1) * 1.f;
                next_pos[1] =  current_pos[1];
            }
            */
            if (is_gonna_encounter_wall[1])
            {
                next_pos[0] = (corner_in_cell[1][0]-1) * 1.f;
                next_pos[1] =  current_pos[1];
            }
        }
    
    for (int j {0}; j < corner_in_cell.size(); j++)
    {
        if (next_pos[0] < -0.25f || corner_in_cell[j][0] > 49)
        {
            is_border = true;
            break;
        } 
        
        if (next_pos[1] > 0.25f ||next_pos[1] < -49)
        {
            is_border = true;
            break;
        }
    }

    if (is_border)
    {
        return current_pos;
    }
    return next_pos;
    
}

void Player::update_player_position(double const deltaTime) 
{
    std::vector<float> current_pos {coord_x,coord_y};
    std::vector<float> next_pos {coord_x,coord_y};
    if (keys_state[GLFW_KEY_W]) {
        next_pos[1] += deltaTime * speed;
    }
    if (keys_state[GLFW_KEY_S]) {
        next_pos[1] -= deltaTime * speed;
    }
    if (keys_state[GLFW_KEY_A]) {
        next_pos[0] -= deltaTime * speed;
    }
    if (keys_state[GLFW_KEY_D]) {
        next_pos[0] += deltaTime * speed;
    }

    next_pos = player_collision_handler(current_pos,next_pos,current_stage,keys_state);
    coord_x = next_pos[0];
    coord_y = next_pos[1];
}

void Player::render_player()
{
    render_map();
    myEngine.mvMatrixStack.pushMatrix();
        Vector3D player_new_pos {player.coord_x*10.f,player.coord_y*10.f, 0.f};
        myEngine.mvMatrixStack.addTranslation(player_new_pos);
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0.f, 1.f, 0.f);
        cell.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void Player::destroy_block()
{
    std::vector<std::vector<float>> new_corners 
    {
        {coord_x , coord_y}, // upper_left
        {coord_x + 1.f, coord_y}, //upper_right
        {coord_x + 1.f, coord_y - 1.f }, //lower_right
        {coord_x , coord_y - 1.f}  //lower_left
    };

    std::vector<std::vector<int>> corner_in_cell{};
    std::vector<bool> is_gonna_encounter_wall { false, false, false, false};

    //calculate currents corners of our player
    for (int i {0}; i < new_corners.size(); i++)
    {   
        corner_in_cell.push_back({static_cast<int>(new_corners[i][0]), static_cast<int>(new_corners[i][1])}); 
    }

    if (keys_state[GLFW_KEY_W]) 
    {
        //Look for walls above player
        if (current_stage.content[(-corner_in_cell[0][1])-1][corner_in_cell[0][0]] == '#')
        {
            is_gonna_encounter_wall[0] = true;
        }
        else
        {
            is_gonna_encounter_wall[0] = false;
        }
        if (current_stage.content[(-corner_in_cell[1][1])-1][corner_in_cell[1][0]] == '#')
        {
            is_gonna_encounter_wall[1] = true;
        }
        else
        {
            is_gonna_encounter_wall[1] = false;
        }
        // Destroy wall above player
        if (is_gonna_encounter_wall[0])
        {
            current_stage.content[(-corner_in_cell[0][1])-1][corner_in_cell[0][0]] = ' ';
        }
        if (is_gonna_encounter_wall[1])
        {
            current_stage.content[(-corner_in_cell[1][1])-1][corner_in_cell[1][0]] = ' ';
        }
    }
    if (keys_state[GLFW_KEY_S]) 
    {
        //Look for walls under player
        if (current_stage.content[(-corner_in_cell[2][1])][corner_in_cell[2][0]] == '#')
        {
            is_gonna_encounter_wall[2] = true;
        }
        else
        {
            is_gonna_encounter_wall[2] = false;
        }
        if (current_stage.content[(-corner_in_cell[3][1])][corner_in_cell[3][0]] == '#')
        {
            is_gonna_encounter_wall[3] = true;
        }
        else
        {
            is_gonna_encounter_wall[3] = false;
        }
        // Destroy wall under player
        if (is_gonna_encounter_wall[2])
        {
            current_stage.content[(-corner_in_cell[2][1])][corner_in_cell[2][0]] = ' ';
        }
        if (is_gonna_encounter_wall[3])
        {
            current_stage.content[(-corner_in_cell[3][1])][corner_in_cell[3][0]] = ' ';
        }
    }
    if (keys_state[GLFW_KEY_A]) 
    {
        //Look for walls to the left of player
        if (current_stage.content[(-corner_in_cell[0][1])][corner_in_cell[0][0]-1] == '#')
        {
            is_gonna_encounter_wall[0] = true;
        }
        else
        {
            is_gonna_encounter_wall[0] = false;
        }
        if (current_stage.content[(-corner_in_cell[3][1])][corner_in_cell[3][0]-1] == '#')
        {
            is_gonna_encounter_wall[3] = true;
        }
        else
        {
            is_gonna_encounter_wall[3] = false;
        }
        // Destroy wall to the left of player
        if (is_gonna_encounter_wall[0])
        {
            current_stage.content[(-corner_in_cell[0][1])][corner_in_cell[0][0]-1] = ' ';
        }
        if (is_gonna_encounter_wall[3])
        {
            current_stage.content[(-corner_in_cell[3][1])][corner_in_cell[3][0]-1] = ' ';
        }
    }
    if (keys_state[GLFW_KEY_D]) 
    {
        //Look for walls to the right of player
        if (current_stage.content[(-corner_in_cell[2][1])][corner_in_cell[2][0]] == '#')
        {
            is_gonna_encounter_wall[2] = true;
        }
        else
        {
            is_gonna_encounter_wall[2] = false;
        }
        if (current_stage.content[(-corner_in_cell[1][1])][corner_in_cell[1][0]] == '#')
        {
            is_gonna_encounter_wall[1] = true;
        }
        else
        {
            is_gonna_encounter_wall[1] = false;
        }
        // Destroy wall above player
        if (is_gonna_encounter_wall[2])
        {
            current_stage.content[(-corner_in_cell[2][1])][corner_in_cell[2][0]] = ' ';
        }
        if (is_gonna_encounter_wall[1])
        {
            current_stage.content[(-corner_in_cell[1][1])][corner_in_cell[1][0]] = ' ';
        }
    }
    
}