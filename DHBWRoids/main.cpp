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
#include "GameObjects.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

const uint16_t WINDOWWIDTH = 1280;
const uint16_t WINDOWHEIGHT = 720;
bool SPIELEN = false;


class GameWindow : public Gosu::Window
{
    std::unique_ptr<Gosu::Image> background_image;
    Gosu::Font font = { 50 };
    std::vector<Projectile> projectiles;
    Player player = {0.965, 0.3, 0,  "media/Starfighter.bmp"};
    Gosu::Song backgroundsong { "Assets/Sounds/SpaceMusic.mp3" };
    std::vector<Asteroid> asteroids;
    int16_t maximum_asteroids = 4;
    uint16_t lives = 3;


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

        //Ship hit?
        for (Asteroid& asteroid : asteroids) {
            if (asteroid.got_hit(player.pos_x, player.pos_y)) {
                lives--;
                player.warp(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);
                if (lives == 0)
                {
                    player.lose.play();
                    close();
                }
            }
        }
        // call player character movement function
        player.move();

        // create new Asteroids with increasing maximum everytime all asteroids are cleared
        if(asteroids.size() == 0) {
            for (size_t i = 0; i < maximum_asteroids; i++) {
                    asteroids.push_back({ Gosu::random(0, WINDOWWIDTH), Gosu::random(0, WINDOWHEIGHT), 5*Gosu::random(-1, 1),5 * Gosu::random(-1,1), Gosu::random(0, 90) });
            }
            maximum_asteroids++;
        }

        // create new projectiles and play sound, reset reload time
        if (Gosu::Input::down(Gosu::KB_SPACE) && (player.reload_time <= 0)) {
            projectiles.push_back({ player.pos_x, player.pos_y, player.vel_x, player.vel_y, player.angle });
            player.reload_time =  10;   //waiting 167ms for next projectile; (10/60)frames per second
            player.beep.play();         //playing projectile sound
        }
        
        // call projectile movement function for all projectiles
        for (Projectile& projectile : projectiles) {
            for (Asteroid& asteroid : asteroids) {
                if (asteroid.got_hit(projectile.pos_x, projectile.pos_y)) {
                    //Asteroid Punktevergabe
                    projectile.pos_x = -100.0;
                    if (asteroid.size == big) {
                        player.score += 1;
                    }
                    if (asteroid.size == medium)
                    {
                        player.score += 5;
                    }
                    if (asteroid.size == little)
                    {
                        player.score += 10;
                    }
                    //create two smaller asteroids
                    if (asteroid.size == big) {
                        double rand1 = Gosu::random(-1, 1);     //random for different angle and speed
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
                    asteroid.pos_y = -100,0;
                }
            }
        }

        //delete hit asteroids
        for (int i = 0; i < asteroids.size(); i++) {
            if (asteroids.at(i).pos_y < 0) {
                asteroids.erase(asteroids.begin()+i);
            }
        }
        //delete off screen projectiles
        for (int i = 0; i < projectiles.size(); i++) {
            if (projectiles.at(i).pos_x > WINDOWWIDTH || projectiles.at(i).pos_x < 0 || projectiles.at(i).pos_y > WINDOWHEIGHT || projectiles.at(i).pos_y < 0) {
                projectiles.erase(projectiles.begin()+i);
            }
        }
        
        //copy temporary asteroids into permanent vector
        for (Asteroid newAsteroid : newAsteroids) {
            asteroids.push_back(newAsteroid);
        }
        // call asteroid movement function for all asteroids
        for (Asteroid& asteroid : asteroids) {
                asteroid.move();
        }
        // call prjectile movement function for all projectiles
        for (Projectile& projectile : projectiles) {
            projectile.move();
        }
        // decrement reload time by 1
        player.reload_time--;

    }

    void draw() override
    {
        //set counter 1 during game
        // call draw function for all gameObjects
        background_image->draw(0, 0, Z_BACKGROUND);
        player.draw();
        for (Asteroid& asteroid : asteroids) {
            asteroid.draw();
        }
        for (Projectile& projectile : projectiles) {
            projectile.draw();
        }
        font.draw_text("Score: " + std::to_string(player.score), 10, 10, Z_UI, 1, 1, Gosu::Color::GREEN);
        font.draw_text("Lives: " + std::to_string(lives), 1100, 10, Z_UI, 1, 1, Gosu::Color::GREEN);
    }

    void button_down(Gosu::Button button) override
    {
        if (button == Gosu::KB_ESCAPE) {
               //set counter 0
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
