#include <iostream>

#include "MyFramework.h"

// Game

Game::Game(int map_x, int map_y, int window_size_x, int window_size_y, int num_enemy, int num_ammo)
    : player(window_size_x, window_size_y, mysprite.player),
      aim(window_size_x, window_size_y, mysprite.aim),
      size_x(window_size_x),
      size_y(window_size_y),
      size_map_x(map_x),
      size_map_y(map_y),
      count_enemy(num_enemy),
      count_ammo(num_ammo) {}

void Game::drawByMap(Coordinates& cord) {
    if (cord.GetX() > pos_x_by_map && cord.GetY() > pos_y_by_map && cord.GetY() < pos_y_by_map + size_y && cord.GetX() < pos_x_by_map + size_x) {
        drawSprite(cord.sprite, cord.GetX() - pos_x_by_map, cord.GetY() - pos_y_by_map);
    }
}

void Game::add_enemy() {
    if (enemies.size() < count_enemy) {
        int size = count_enemy - enemies.size();
        for (int i = 0; i < size; i++) {
            enemies.emplace_back(size_map_x, size_map_y, player.pixel_x, player.pixel_y, player.GetX(), player.GetY(), mysprite.enemy);
        }
    }
}
