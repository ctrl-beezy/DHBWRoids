#pragma once
#include <string>
#include <Gosu/Gosu.hpp>


extern uint16_t WINDOWWIDTH;
extern uint16_t WINDOWHEIGHT;

class GameObject
{
public:
    Gosu::Image image;
    Gosu::Sample beep;
    double pos_x, pos_y, vel_x, vel_y, angle;

    GameObject(std::string filename) : image(filename)
    {
        pos_x = pos_y = vel_x = vel_y = angle = 0;
    }

    void warp(double x, double y)
    {
        pos_x = x;
        pos_y = y;
    }
    void draw() const
    {
        image.draw_rot(pos_x, pos_y, 1, angle);
    }
};

class Player : public GameObject {

public:

    uint32_t score;
    double drag, accel;
    
    Player(std::string filename = "media/Starfighter.bmp", double d = 0.95, double a = 0.6, uint32_t s = 0) : GameObject(filename) {
        drag = d;
        accel = a;
        score = s;
    }
    void turn_left()
    {
        angle -= 4.5;
    }

    void turn_right()
    {
        angle += 4.5;
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

class Asteroid : public GameObject {

public:
    uint32_t size;

    Asteroid(std::string filename, double drag, double a, uint32_t s) : GameObject(filename) {
        size = s;
    }
};

class Projectile : public GameObject {
    Projectile(std::string filename = ) : image(filename)
    {
        pos_x = pos_y = vel_x = vel_y = angle = 0;
    }
};