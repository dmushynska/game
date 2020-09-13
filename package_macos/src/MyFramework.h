#pragma once
#include <ctime>
#include <deque>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "Framework.h"
class Game;
class Coordinates;
class Enemy;
class Player;
struct MovePlayer;

// function
void find(float& from_x, float& from_y, float to_x, float to_y);
bool isIntersection(Coordinates& cord1, Coordinates& cord2);
void logical_move(Game& game);
int crandom(int x);

struct MySprite {
    Sprite* enemy = nullptr;
    Sprite* player = nullptr;
    Sprite* aim = nullptr;
    Sprite* ammo = nullptr;
};

struct Pixels {
    int middle_x;
    int middle_y;
};

struct MovePlayer {
    bool right;
    bool left;
    bool up;
    bool down;
};

class Coordinates {
protected:
    float m_x = 0;
    float m_y = 0;

public:
    Sprite* sprite;
    int pixel_x;
    int pixel_y;
    Pixels pixels;

    Coordinates() = default;

    Coordinates(float x, float y);

    virtual ~Coordinates() = default;

    Coordinates& operator=(const Coordinates& cord);

    Coordinates(const Coordinates& cord) = default;

    Coordinates(Coordinates&& c);

    void create_pixels(int x, int y);

    float GetX();

    float GetY();
};

// прицел
class Aim : public Coordinates {
public:
    Aim(float _x, float _y, Sprite* mysprite) : Coordinates(_x / 2, _y / 2) {
        sprite = mysprite;
    }
    ~Aim() = default;
    void moveaim(float _x, float _y, float pos_map_x, float pos_map_y) {
        m_x = _x + pos_map_x;
        m_y = _y + pos_map_y;
    }
};

class Player : public Coordinates {
public:
    Player(float _x, float _y, Sprite* mysprite);
    ~Player() = default;
    void Restart(int map_size_x, int map_size_y);
    void moveplayer(MovePlayer& k, Game& game);
};

class Enemy : public Coordinates {
public:
    int m_random = crandom(3) + 1;

    Enemy(const Enemy& e1);

    Enemy& operator=(const Enemy& e1);

    Enemy(float x, float y, float play_x, float play_y, float pos_play_x, float pos_play_y, Sprite* mysprite);

    ~Enemy() = default;

    void moveenemy(float pleyer_x, float pleyer_y);
};

// боеприпасы
class Ammo : public Coordinates {
    bool isRealised;
    float aim_x;
    float aim_y;

public:
    float end_x;
    float end_y;

    Ammo(Sprite* mysprite);

    ~Ammo() = default;

    Ammo(const Ammo& am);

    Ammo& operator=(const Ammo& am);

    void findpath(float x, float y, float play_pixels_middle_x, float play_pixels_middle_y);

    void moveammo();
};

class Game {
public:
    MySprite mysprite;
    bool isGetTickCount = true;
    Player player;
    Aim aim;
    std::vector<Enemy> enemies;
    std::deque<Ammo> ammo;
    size_t count_enemy = 10;
    size_t count_ammo = 3;
    MovePlayer movePlayer;
    int size_x = 500;
    int size_y = 500;
    int size_map_x = 800;
    int size_map_y = 800;
    int pos_x_by_map = 0;
    int pos_y_by_map = 0;

    Game(int map_x, int map_y, int window_size_x, int window_size_y, int num_enemy, int num_ammo);

    void drawByMap(Coordinates& cord);

    void add_enemy();
};

/* Test Framework realization */
class MyFramework : public Framework {
    Game gameplay;

public:
    MyFramework(int map_x, int map_y, int window_size_x, int window_size_y, int num_enemies, int num_ammo);

    void Restart();

    void PreInit(int& width, int& height, bool& fullscreen) override;

    bool Init() override;

    void Close() override;

    bool Tick() override;

    void onMouseMove(int x, int y, int xrelative, int yrelative) override;

    void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

    void onKeyPressed(FRKey k) override;

    void onKeyReleased(FRKey k) override;
};