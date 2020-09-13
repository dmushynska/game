#include "MyFramework.h"

// Enemy

    Enemy::Enemy(const Enemy& e1) : Coordinates(e1) {}

    Enemy& Enemy::operator=(const Enemy& e1) {
        Coordinates::operator=(e1);
        return *this;
    }

int random_enemy(int player_pixels, int pos_player_m_x_y, int pixels_size, int max_x_y) {
    int random = crandom(max_x_y);

    while (random > pos_player_m_x_y - player_pixels && random < pos_player_m_x_y + (2 * player_pixels)) {
        random = crandom(max_x_y);
    }
    return random;
}

Enemy::Enemy(float size_map_x, float size_map_y, float player_pixel_x, float player_pixel_y, float pos_player_x, float pos_player_y, Sprite* mysprite) {
    sprite = mysprite;
    m_x = random_enemy(player_pixel_x, pos_player_x, pixel_x, size_map_x);
    m_y = random_enemy(player_pixel_y, pos_player_y, pixel_y, size_map_y);
    getSpriteSize(sprite, pixel_x, pixel_y);
    create_pixels(m_x, m_y);
}

void Enemy::moveenemy(float pleyer_x, float pleyer_y) {
    float x = pixels.middle_x, y = pixels.middle_y;
    find(x, y, pleyer_x, pleyer_y);
    m_x -= (x * 0.08 * m_random);
    m_y -= (y * 0.08 * m_random);
    create_pixels(m_x, m_y);
}