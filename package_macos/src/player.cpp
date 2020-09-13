#include "MyFramework.h"

// Player

void Player::Restart(int map_size_x, int map_size_y) {
    m_x = map_size_x / 2 - 24;
    m_y = map_size_y / 2 - 24;
}

void Player::moveplayer(MovePlayer& k, Game& game) {
    if (k.right == true) {
        if (game.size_map_x - (game.pos_x_by_map + game.size_x) != 0 && m_x >= game.size_x / 2)
            game.pos_x_by_map++;
        if (m_x < game.size_map_x - pixel_x - 1)
            m_x++;
    }
    if (k.down == true) {
        if (game.size_map_y - (game.pos_y_by_map + game.size_y) != 0 && m_y >= game.size_y / 2)
            game.pos_y_by_map++;
        if (m_y != game.size_map_y - pixel_y - 1)
            m_y++;
    }
    if (k.left == true) {
        if (game.pos_x_by_map != 0 && m_x < game.size_map_x - (game.size_x / 2))
            game.pos_x_by_map--;
        if (m_x > 1)
            m_x--;
    }
    if (k.up == true) {
        if (game.pos_y_by_map != 0 && m_y < game.size_map_y - (game.size_y / 2))
            game.pos_y_by_map--;
        if (m_y > 1)
            m_y--;
    }

    create_pixels(m_x, m_y);
}

Player::Player(float size_x, float size_y, Sprite* mysprite) : Coordinates(size_x / 2 - 24, size_y / 2 - 24) {
    sprite = mysprite;
    create_pixels(m_x, m_y);
}