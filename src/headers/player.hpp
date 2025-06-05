#pragma once

#include "key_options.hpp"
#include "map.hpp"

struct Player
{
    float coord_x {};
    float coord_y {};
    std::vector<bool> keys_state {};
    float speed {10.f};
    Map current_stage{};
    int score {0};
    bool is_alive  {true};

    void update_player_position(double const deltaTime);
    void render_player();
    void destroy_block();
};

extern Player player;

void key_callback_player(GLFWwindow* window, int key, int scancode, int action, int mods);
Player init_player(float start_coord_x, float start_coord_y);

std::vector<float> player_collision_handler(std::vector<float> const& current_pos,std::vector<float> & next_pos, Map & map, std::vector<bool> keys_state);


