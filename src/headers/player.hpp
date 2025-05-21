#pragma once

#include "key_options.hpp"
#include "map.hpp"

struct Player
{
    float coord_x {};
    float coord_y {};
    std::vector<bool> keys_state {};

    float speed {2.f};
    void update_player_position(double const deltaTime);
    void render_player();
};

extern Player player;

void key_callback_player(GLFWwindow* window, int key, int scancode, int action, int mods);
Player init_player(float start_coord_x, float start_coord_y);




