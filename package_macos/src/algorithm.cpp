#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include "MyFramework.h"

int crandom(int x) {
    return rand() % x;
}

void find(float& from_x, float& from_y, float to_x, float to_y) {
    float del_x = from_x - to_x;
    float del_y = from_y - to_y;
    float length = std::sqrt(del_x * del_x + del_y * del_y);
    from_x = del_x / length;
    from_y = del_y / length;
}

bool isIntersection(Coordinates &cord1, Coordinates &cord2) {
    return ((cord2.GetX() - cord1.GetX()) * (cord2.GetX() - cord1.GetX())) + ((cord2.GetY() - cord1.GetY()) * (cord2.GetY() - cord1.GetY())) < (cord1.pixel_x / 2 + cord2.pixel_x / 2) * (cord1.pixel_y / 2 + cord2.pixel_y / 2);
}

void logical_move(Game &game) {
    for (auto it = game.enemies.begin(); it != game.enemies.end(); it++) {
        drawSprite(it->sprite, it->GetX(), it->GetY());
        for (auto ammo = game.ammo.begin(); ammo != game.ammo.end(); ) {
            if (isIntersection(*(it), *(ammo)) == true) {
                ammo = game.ammo.erase(ammo);
                it = game.enemies.erase(it);
            } else {
                ammo++;
            }
        }
        if (it == game.enemies.end()) {
            break;
        }
    }
}
