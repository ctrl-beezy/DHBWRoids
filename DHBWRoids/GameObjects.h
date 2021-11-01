#pragma once
#include <string>
#include <Gosu/Gosu.hpp>
#include <cmath>
#include <cstdint>


const extern uint16_t WINDOWWIDTH;
const extern uint16_t WINDOWHEIGHT;

enum ZOrder {
    Z_BACKGROUND,
    Z_OBJECTS,
    Z_UI
};

enum AsteroidSize {
    noSize,
    little,
    medium,
    big,
};


class GameObject
{
public:
    Gosu::Image image;

    double pos_x, pos_y, vel_x, vel_y, angle , drag;

    GameObject(std::string filename) : image(filename)
    {
        pos_x = pos_y = vel_x = vel_y = angle = 0;
        drag = 1;
    }

    void warp(double x, double y)
    {
        pos_x = x;
        pos_y = y;
    }
    void draw() const
    {
        image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle, 0.4, 0.5, 1, 1);
    }

    void move()
    {
        pos_x = Gosu::wrap(pos_x + vel_x, 0.0, double(WINDOWWIDTH));
        pos_y = Gosu::wrap(pos_y + vel_y, 0.0, double(WINDOWHEIGHT));

        vel_x *= drag;
        vel_y *= drag;
    }
};

class Player : public GameObject {

public:
    uint32_t score;
    double drag, accel;
    int16_t reload_time;
    Gosu::Sample beep;
    Gosu::Sample lose;
    
    Player(double d = 1.0, double a = 0.5, uint32_t s = 0, std::string filename = "media/Starfighter.bmp", std:: string soundname = "Assets/Sounds/laser.wav", std::string losesound = "Assets/Sounds/explosion.wav") : GameObject(filename), beep(soundname), lose(losesound) {
        drag = d;
        accel = a;
        score = s;
        reload_time = 0;
    }
    void turn_left()
    {
        angle -= 5;
    }

    void turn_right()
    {
        angle += 5;
    }

    void accelerate()
    {
        vel_x += Gosu::offset_x(angle, accel);
        vel_y += Gosu::offset_y(angle, accel);
    }

    void deaccelerate()
    {
        vel_x -= Gosu::offset_x(angle, accel);
        vel_y -= Gosu::offset_y(angle, accel);
    }
    void move()
    {
        pos_x = Gosu::wrap(pos_x + vel_x, 0.0, double(WINDOWWIDTH));
        pos_y = Gosu::wrap(pos_y + vel_y, 0.0, double(WINDOWHEIGHT));

        vel_x *= drag;
        vel_y *= drag;
    }
};
class Projectile : public GameObject {
public:
    Projectile(double x = 0.0, double y = 0.0, double v_x = 0.0, double v_y = 0.0, double a = 0.0, std::string filename = "Assets/Bilder/bullet.png") : GameObject(filename)
    {
        pos_x = x;
        pos_y = y;
        vel_x = v_x;
        vel_y = v_y;
        angle = a;
    }
    void move()
    {
        pos_x += 25*sin(Gosu::degrees_to_radians(angle));
        pos_y -= 25*cos(Gosu::degrees_to_radians(angle));
    }
    void draw() const
    {
        image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle + 90, 1, 0.63, 2.5, 2);
    }
};

class Asteroid : public GameObject {
public:
    uint16_t size;
    Asteroid(double x = 0.0, double y = 0.0, double v_x = 0.0, double v_y = 0.0, double a = 0.0, std::string filename = "Assets/Bilder/asteroid.png", AsteroidSize s = big) : GameObject(filename)
    {
        pos_x = x;
        pos_y = y;
        vel_x = v_x;
        vel_y = v_y;
        angle = a;
        size = s;
    }
    void draw() const
    {
        image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle, 0.5, 0.5, size, size);
    }

    bool got_hit(double object_pos_x, double object_pos_y) {
        return Gosu::distance(pos_x, pos_y, object_pos_x, object_pos_y) < sqrt(image.width()/2 * image.width()/2 + image.height()/2 * image.height()/2);
    }
};