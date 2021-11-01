#include "GameObjects.h"
#include <string>
#include <Gosu/Gosu.hpp>
#include <cmath>
#include <cstdint>


void GameObject::warp(double x, double y)
{
    pos_x = x;
    pos_y = y;
}
void GameObject::draw() const
{
    image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle, 0.4, 0.5, 1, 1);
}

void GameObject::move()
{
    pos_x = Gosu::wrap(pos_x + vel_x, 0.0, double(WINDOWWIDTH));
    pos_y = Gosu::wrap(pos_y + vel_y, 0.0, double(WINDOWHEIGHT));

    vel_x *= drag;
    vel_y *= drag;
}

void Player::turn_left()
{
    angle -= 5;
}

void Player::turn_right()
{
    angle += 5;
}

void Player::accelerate()
{
    vel_x += Gosu::offset_x(angle, accel);
    vel_y += Gosu::offset_y(angle, accel);
}

void Player::deaccelerate()
{
    vel_x -= Gosu::offset_x(angle, accel);
    vel_y -= Gosu::offset_y(angle, accel);
}
void Player::move()
{
    pos_x = Gosu::wrap(pos_x + vel_x, 0.0, double(WINDOWWIDTH));
    pos_y = Gosu::wrap(pos_y + vel_y, 0.0, double(WINDOWHEIGHT));

    vel_x *= drag;
    vel_y *= drag;
}


void Projectile::move()
{
    pos_x += 25 * sin(Gosu::degrees_to_radians(angle));
    pos_y -= 25 * cos(Gosu::degrees_to_radians(angle));
}
void Projectile::draw() const
{
    image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle + 90, 1, 0.63, 2.5, 2);
}

void Asteroid::draw() const
{
    image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle, 0.5, 0.5, size, size);
}

bool Asteroid::got_hit(const double object_pos_x,const double object_pos_y) {
    return Gosu::distance(pos_x, pos_y, object_pos_x, object_pos_y) < sqrt(image.width() / 1.2 * image.width() / 1.2 + image.height() / 1.2 * image.height() / 1.2);
}