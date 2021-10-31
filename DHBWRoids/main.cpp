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
    Player player = {0.98, 0.3, 0,  "media/Starfighter.bmp"};
    Gosu::Song backgroundsong { "Assets/Sounds/SpaceMusic.mp3" };
    std::vector<Asteroid> asteroids;
    uint16_t maximum_asteroids = 4;


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
        }
        // create new Asteroids with a maximum of 4
        while (asteroids.size() < maximum_asteroids) {
            asteroids.push_back({ Gosu::random(0, WINDOWWIDTH), Gosu::random(0, WINDOWHEIGHT), 5*Gosu::random(0, 1),5 * Gosu::random(0,1), Gosu::random(0, 90) });
        }
        
        // call player character movement function
        player.move();
        
        // call projectile movement function for all projectiles
        for (Projectile& projectile : projectiles) {
            projectile.move();
        }
        for (Asteroid& asteroid : asteroids) {
            asteroid.move();
        }
        // decrement reload time by 1
        player.reload_time--;

    }

    void draw() override
    {
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
