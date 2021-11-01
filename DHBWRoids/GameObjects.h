#pragma once
#include <string>
#include <Gosu/Gosu.hpp>
#include <cmath>
#include <cstdint>


const extern uint16_t WINDOWWIDTH;
const extern uint16_t WINDOWHEIGHT;

//enum for draw heights
enum ZOrder {
    Z_BACKGROUND,
    Z_OBJECTS,
    Z_UI,
    Z_MENUE
};

// enum for Asteroidsizes
enum AsteroidSize {
    noSize,
    little,
    medium,
    big,
};

// parent class for all game objects
class GameObject
{
public:
//properties
    Gosu::Image image;
    double pos_x, pos_y, vel_x, vel_y, angle , drag;
    
    GameObject(std::string filename) : image(filename)
    {
        pos_x = pos_y = vel_x = vel_y = angle = 0;
        drag = 1;
    }

    //methods
    void warp(double x, double y);
    void draw() const;
    void move();
};

// class for player character
class Player : public GameObject {

public:
    //properties
    uint32_t score;
    uint16_t lives;
    double drag, accel;
    int16_t reload_time;
    Gosu::Sample beep;
    Gosu::Sample loss;
    Gosu::Sample lose;
    
    Player(double d = 1.0, double a = 0.5, uint32_t s = 0, std::string filename = "media/Starfighter.bmp", std::string soundname = "Assets/Sounds/laser.wav", std::string loss = "Assets/Sounds/Loss1.wav", std::string losesound = "Assets/Sounds/Lose-Sound.wav") : GameObject(filename), beep(soundname), loss(loss), lose(losesound) {
        drag = d;
        accel = a;
        score = s;
        reload_time = 0;
        lives = 3;
    }
    //methods
    void turn_left();
    void turn_right();
    void accelerate();
    void deaccelerate();
    void move();
};
// class for projectiles
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
    
    //methods
    void move();
    void draw() const;
};

// class for asteroids
class Asteroid : public GameObject {
public:
    //properties
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
    
    //methods
    void draw() const;
    bool got_hit(const double object_pos_x, const double object_pos_y);
};