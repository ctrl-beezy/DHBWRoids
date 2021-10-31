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
        image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle, 0.4, 0.4, 1, 1);
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
    
    Player(double d = 0.96, double a = 0.5, uint32_t s = 0, std::string filename = "media/Starfighter.bmp", std:: string soundname = "Assets/Sounds/Laser-Sound.wav") : GameObject(filename), beep(soundname) {
        drag = d;
        accel = a;
        score = s;
        reload_time = 0;
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
        pos_x += std::max<double>(vel_x + 10 * sin(Gosu::degrees_to_radians(angle)), 10 * sin(Gosu::degrees_to_radians(angle)));
        pos_y += std::min<double>(vel_y - 10*cos(Gosu::degrees_to_radians(angle)),-10*cos(Gosu::degrees_to_radians(angle)));
    }
    void draw() const
    {
        image.draw_rot(pos_x, pos_y, Z_OBJECTS, angle + 90, 1, 0.63, 2.5, 2);
    }
};