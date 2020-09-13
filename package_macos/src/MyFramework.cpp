#include "MyFramework.h"

#include <chrono>
#include <iostream>
#include <thread>
// MyFramework

MyFramework::MyFramework(int map_x, int map_y, int window_size_x, int window_size_y, int num_enemies, int num_ammo) : gameplay(map_x, map_y, window_size_x, window_size_y, num_enemies, num_ammo) {
    if (gameplay.size_x > gameplay.size_map_x)
        gameplay.size_map_x = gameplay.size_x;
    if (gameplay.size_y > gameplay.size_map_y)
        gameplay.size_map_y = gameplay.size_x;
}

void MyFramework::Restart() {
    gameplay.enemies.clear();
    gameplay.ammo.clear();
    gameplay.pos_x_by_map = 0;
    gameplay.pos_y_by_map = 0;
    gameplay.player.Restart(gameplay.size_x, gameplay.size_y);
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
    width = gameplay.size_x;
    height = gameplay.size_y;
    fullscreen = false;
}

bool MyFramework::Init() {
    gameplay.mysprite.aim = createSprite("data/reticle.png");
    gameplay.mysprite.ammo = createSprite("data/bullet.png");
    gameplay.mysprite.enemy = createSprite("data/enemy.png");
    gameplay.mysprite.player = createSprite("data/avatar.png");
    if (gameplay.mysprite.player == nullptr || gameplay.mysprite.aim == nullptr || gameplay.mysprite.ammo == nullptr || gameplay.mysprite.enemy == nullptr)
        return false;
    getSpriteSize(gameplay.mysprite.aim, gameplay.aim.pixel_x, gameplay.aim.pixel_y);
    getSpriteSize(gameplay.mysprite.player, gameplay.player.pixel_x, gameplay.player.pixel_y);
    gameplay.player.sprite = gameplay.mysprite.player;
    gameplay.aim.sprite = gameplay.mysprite.aim;
    return true;
}

float vector_length(float from_x, float from_y, float to_x, float to_y) {
    float del_x = from_x - to_x;
    float del_y = from_y - to_y;
    return std::sqrt(del_x * del_x + del_y * del_y);
}

bool MyFramework::Tick() {
    logical_move(gameplay);
    showCursor(false);
    drawTestBackground();
    gameplay.player.moveplayer(gameplay.movePlayer, gameplay);
    gameplay.drawByMap(gameplay.player);
    gameplay.drawByMap(gameplay.aim);
    gameplay.add_enemy();
    for (auto it = gameplay.ammo.begin(); it != gameplay.ammo.end(); it++) {
        (*it).moveammo();
        gameplay.drawByMap(*it);
    }
    for (auto it = gameplay.enemies.begin(); gameplay.enemies.end() != it; it++) {
        if (isIntersection((*it), gameplay.player) == true) {
            Restart();
            return false;
        }
        it->moveenemy(gameplay.player.pixels.middle_x, gameplay.player.pixels.middle_y);
    }
    for (auto it = gameplay.enemies.begin(); gameplay.enemies.end() != it; it++) {
        for (auto now = gameplay.enemies.begin(); gameplay.enemies.end() != now; now++) {
            if (isIntersection(*it, *now) == true) {
                if (vector_length(it->GetX(), it->GetY(), gameplay.player.GetX(), gameplay.player.GetY()) < vector_length(now->GetX(), now->GetY(), gameplay.player.GetX(), gameplay.player.GetY()))
                    it->moveenemy(gameplay.player.pixels.middle_x, gameplay.player.pixels.middle_y);
                else
                    now->moveenemy(gameplay.player.pixels.middle_x, gameplay.player.pixels.middle_y);
            }
            gameplay.drawByMap(*it);
        }
    }
    return false;
}

void MyFramework::Close() {
    destroySprite(gameplay.mysprite.aim);
    destroySprite(gameplay.mysprite.ammo);
    destroySprite(gameplay.mysprite.enemy);
    destroySprite(gameplay.mysprite.player);
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
    gameplay.aim.moveaim(x, y, gameplay.pos_x_by_map, gameplay.pos_y_by_map);
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    if (FRMouseButton::LEFT == button && isReleased == true) {
        gameplay.ammo.emplace_front(gameplay.mysprite.ammo);
        gameplay.ammo.front().findpath(gameplay.aim.GetX(), gameplay.aim.GetY(), gameplay.player.pixels.middle_x, gameplay.player.pixels.middle_y);
        if (gameplay.count_ammo < gameplay.ammo.size())
            gameplay.ammo.pop_back();
    }
    gameplay.drawByMap(gameplay.player);
}

void MyFramework::onKeyPressed(FRKey k) {
    if (k == FRKey::RIGHT)
        gameplay.movePlayer.right = true;
    else if (k == FRKey::LEFT)
        gameplay.movePlayer.left = true;
    else if (k == FRKey::UP)
        gameplay.movePlayer.up = true;
    else if (k == FRKey::DOWN)
        gameplay.movePlayer.down = true;
}

void MyFramework::onKeyReleased(FRKey k) {
    if (k == FRKey::RIGHT)
        gameplay.movePlayer.right = false;
    else if (k == FRKey::LEFT)
        gameplay.movePlayer.left = false;
    else if (k == FRKey::UP)
        gameplay.movePlayer.up = false;
    else if (k == FRKey::DOWN)
        gameplay.movePlayer.down = false;
}
