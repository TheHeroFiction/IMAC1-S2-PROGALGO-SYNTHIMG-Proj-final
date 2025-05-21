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


void Player::update_player_position(double const deltaTime) 
{
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
    coord_x = next_pos[0];
    coord_y = next_pos[1];
    //_player_position = handle_collision_with_level(_player_position, next_position, _level);
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