// The complete Gosu library.
#include <Gosu/Gosu.hpp>
// Makes life a little easier when compiling the game in Visual C++.
#include <Gosu/AutoLink.hpp>

#include <Windows.h>
#include <cstdlib>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "game_math.h"
#include "GameObjects.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

const uint16_t WINDOWWIDTH = 1280;
const uint16_t WINDOWHEIGHT = 720;


class GameWindow : public Gosu::Window
{
    std::unique_ptr<Gosu::Image> background_image;
    Gosu::Font font = { 50 };
    std::vector<Projectile> projectiles;
    Player player = {0.965, 0.3, 0,  "media/Starfighter.bmp"};
    Gosu::Song backgroundsong { "Assets/Sounds/SpaceMusic.mp3" };
    std::vector<Asteroid> asteroids;
    int16_t maximum_asteroids = 4;


public:
    GameWindow() : Window(WINDOWWIDTH, WINDOWHEIGHT, false)
    {
        set_caption("DHBWROIDS");
        std::string filename = "Assets/Bilder/space.png";
        background_image.reset(new Gosu::Image(filename, Gosu::IF_TILEABLE));

        player.warp(WINDOWWIDTH/2, WINDOWHEIGHT/2);
        player.image.data();
        
    }


    void update() override
    {
        //temporary vector to store new Asteroids
        std::vector<Asteroid> newAsteroids;
        
        // loop song
        if (!backgroundsong.playing()) {
            backgroundsong.play();
        }
        // player movement inputs
        if (Gosu::Input::down(Gosu::KB_A)) {
            player.turn_left();
        }
        if (Gosu::Input::down(Gosu::KB_D)) {
            player.turn_right();
        }
        if (Gosu::Input::down(Gosu::KB_W)) {
            player.accelerate();
        }

        // create new Asteroids with increasing maximum everytime all asteroids are cleared
        if(asteroids.size() == 0) {
            for (size_t i = 0; i < maximum_asteroids; i++) {
                    asteroids.push_back({ Gosu::random(0, WINDOWWIDTH), Gosu::random(0, WINDOWHEIGHT), 5*Gosu::random(-1, 1),5 * Gosu::random(-1,1), Gosu::random(0, 90) });
            }
        }

        // delete off screen projectiles
        if(projectiles.size() > 0){
            auto i = std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile o) {return (o.pos_x < 0 || o.pos_y < 0 || o.pos_x > WINDOWWIDTH || o.pos_y > WINDOWHEIGHT);});
            if (i != projectiles.end()) {
                projectiles.erase(i);
            }
        }
        // create new projectiles and play sound, reset reload time
        if (Gosu::Input::down(Gosu::KB_SPACE) && (player.reload_time <= 0)) {
            projectiles.push_back({ player.pos_x, player.pos_y, player.vel_x, player.vel_y, player.angle });
            player.reload_time = 15;
            player.beep.play();
            // check collision with asteroids
        }
        // call player character movement function
        player.move();
        
        // call projectile movement function for all projectiles
        for (Projectile& projectile : projectiles) {
            projectile.move();
            for (Asteroid& asteroid : asteroids) {
                if (asteroid.got_hit(projectile.pos_x, projectile.pos_y)) {
                    //Asteroid hit
                    projectile.pos_x = -100;
                    //create two smaller asteroids
                    if (asteroid.size == big) {
                        double rand1 = Gosu::random(-1, 1);
                        double rand2 = Gosu::random(-1, 1);
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 6*rand1, 6*rand2, rand1, "Assets/Bilder/asteroid.png", medium});
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 6*rand2, 6*rand1, rand2, "Assets/Bilder/asteroid.png", medium});
                    }
                    if (asteroid.size == medium) {
                        double rand1 = Gosu::random(-1,1);
                        double rand2 = Gosu::random(-1,1);
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 7*rand1, 7*rand1, Gosu::random(0,90), "Assets/Bilder/asteroid.png", little});
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 7*rand2, 7*rand2, Gosu::random(0,90), "Assets/Bilder/asteroid.png", little});

                    }
                    asteroid.pos_x = -100;
                }
            }
        }
        //delete hit asteroids
        if (asteroids.size() > 0) {
            auto i = std::remove_if(asteroids.begin(), asteroids.end(), [&](Asteroid o) {return (o.pos_x < 0); });
            if (i != asteroids.end()) {
                asteroids.erase(i);
            }
        }
        for (Asteroid newAsteroid : newAsteroids) {
            asteroids.push_back(newAsteroid);
        }
        // call asteroid movement function for all asteroids
        for (Asteroid& asteroid : asteroids) {
            asteroid.move();
        }
        // decrement reload time by 1
        player.reload_time--;

    }

    void draw() override
    {
        // call draw function for all gameObjects
        player.draw();
        background_image->draw(0, 0, Z_BACKGROUND);
        for (Projectile& projectile : projectiles) {
            projectile.draw();
        }
        for (Asteroid& asteroid : asteroids) {
            asteroid.draw();
        }
        font.draw_text("Score: " + std::to_string(player.score), 10, 10, Z_UI, 1, 1, Gosu::Color::GREEN);
    }

    void button_down(Gosu::Button button) override
    {
        if (button == Gosu::KB_ESCAPE) {
            close();
        }
        else {
            Window::button_down(button);
        }
    }
};

int main()
{
    std::srand(std::time(0));
    GameWindow window;
	window.show();
}
