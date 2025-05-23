#include "player.hpp"

Player player {init_player(0.f,0.f)};

void key_callback_player(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    // update _keysState
    if (key >= 0 && key < player.keys_state.size()) {
        player.keys_state[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
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

std::vector<float> player_collision_handler(std::vector<float> const& current_pos,std::vector<float> const& next_pos, Map const& map)
{
    std::vector<float> new_corners 
    {
        next_pos[0] - 0.5f, next_pos[1] + 0.5f,
        next_pos[0] + 0.5f, next_pos[1] + 0.5f,
        next_pos[0] + 0.5f, next_pos[1] - 0.5f,
        next_pos[0] - 0.5f, next_pos[1] - 0.5f
    };

    std::vector<int> corner_in_cell{};
    bool is_gonna_encounter_wall {false};

    for (int i {0}; i < new_corners.size(); i+=2)
    {
        if ((new_corners[i] - static_cast<int>(new_corners[i])) < 0.5f)
        {
            corner_in_cell.push_back(static_cast<int>(new_corners[i]));
        }
        else
        {
            corner_in_cell.push_back(static_cast<int>(new_corners[i])+1);
        }

        if ((static_cast<int>(new_corners[i+1]) - new_corners[i+1]) < 0.5f)
        {
            corner_in_cell.push_back(static_cast<int>(new_corners[i+1]));
        }
        else
        {
            corner_in_cell.push_back(static_cast<int>(new_corners[i+1])+1);
        }
    }

    for (int j {0}; j < corner_in_cell.size(); j+=2)
    {
        std::cout<< j << "corner x: " << corner_in_cell[j] << ", corner y: " << corner_in_cell[j+1] << std::endl;
        if (next_pos[0] < -0.25f || corner_in_cell[j] > 49)
        {
            is_gonna_encounter_wall = true;
            break;
        } 
        
        if (next_pos[1] > 0.25f ||next_pos[1] < -49)
        {
            is_gonna_encounter_wall = true;
            break;
        }
        
        if (map.content[corner_in_cell[j]][-corner_in_cell[j+1]] == '#')
        {
            is_gonna_encounter_wall = true;
            break;
        }

    }

    if (is_gonna_encounter_wall)
    {
        return current_pos;
    }
    else 
    {
        return next_pos;
    }
}

void Player::update_player_position(double const deltaTime, Map const& map) 
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

    next_pos = player_collision_handler(current_pos,next_pos,map);
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