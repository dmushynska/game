#include "MyFramework.h"

// Ammo

    Ammo::Ammo(const Ammo& am) : Coordinates(am), isRealised(am.isRealised), aim_x(am.aim_x), aim_y(am.aim_y), end_x(am.end_x), end_y(am.end_y) {}

    Ammo& Ammo::operator=(const Ammo& am) {
        Coordinates::operator=(am);
        aim_x = am.aim_x;
        aim_y = am.aim_y;
        end_x = am.end_x;
        end_y = am.end_y;
        return *this;
    }

Ammo::Ammo(Sprite* mysprite) {
    sprite = mysprite;
    getSpriteSize(sprite, pixel_x, pixel_y);
}

void Ammo::findpath(float x, float y, float play_pixels_middle_x, float play_pixels_middle_y) {
    isRealised = true;
    end_x = x;
    end_y = y;

    m_x = play_pixels_middle_x;
    m_y = play_pixels_middle_y;
    aim_x = play_pixels_middle_x;
    aim_y = play_pixels_middle_y;
    find(aim_x, aim_y, x, y);
    create_pixels(m_x, m_y);
}

void Ammo::moveammo() {
    if (isRealised) {
        m_x -= aim_x;
        m_y -= aim_y;
        create_pixels(m_x, m_y);
    }
}
