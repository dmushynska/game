#include "MyFramework.h"

Coordinates& Coordinates::operator=(const Coordinates& cord) {
    sprite = std::move(cord.sprite);
    pixels = cord.pixels;
    m_x = cord.m_x;
    m_y = cord.m_y;
    pixel_x = cord.pixel_x;
    pixel_y = cord.pixel_y;
    return *this;
}

Coordinates::Coordinates(float _x, float _y) : m_x(_x), m_y(_y) {}

Coordinates::Coordinates(Coordinates&& c)
    : m_x(c.m_x), m_y(c.m_y), sprite(c.sprite), pixel_x(c.pixel_x), pixel_y(c.pixel_y), pixels(c.pixels) {
    c.sprite = nullptr;
}

void Coordinates::create_pixels(int x, int y) {
    pixels.middle_x = x + (pixel_x / 2);
    pixels.middle_y = y + (pixel_y / 2);
}

float Coordinates::GetX() {
    return m_x;
}

float Coordinates::GetY() {
    return m_y;
}
