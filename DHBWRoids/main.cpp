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

const uint16_t WINDOWWIDTH = 1280;
const uint16_t WINDOWHEIGHT = 720;


class GameWindow : public Gosu::Window
{
    std::unique_ptr<Gosu::Image> background_image;
    Gosu::Font font = { 50 };
    std::vector<Projectile> projectiles;
    Player player = {0.98, 0.3, 0,  "media/Starfighter.bmp"};
    Gosu::Song backgroundsong { "Assets/Sounds/SpaceMusic.mp3" };

public:
    GameWindow()
        : Window(WINDOWWIDTH, WINDOWHEIGHT, false)
    {
        set_caption("DHBWROIDS");
        std::string filename = "Assets/Bilder/space.png";
        background_image.reset(new Gosu::Image(filename, Gosu::IF_TILEABLE));

        player.warp(WINDOWWIDTH/2, WINDOWHEIGHT/2);
        player.image.data();
    }

    void update() override
    {
        if (!backgroundsong.playing()) {
            backgroundsong.play();
        }
        if (Gosu::Input::down(Gosu::KB_A)) {
            player.turn_left();
        }
        if (Gosu::Input::down(Gosu::KB_D)) {
            player.turn_right();
        }
        if (Gosu::Input::down(Gosu::KB_W)) {
            player.accelerate();
        }
        if (Gosu::Input::down(Gosu::KB_S)) {
            player.deaccelerate();
        }
        player.move();
        if (Gosu::Input::down(Gosu::KB_SPACE) && (player.reload_time <= 0)) {
            projectiles.push_back({ player.pos_x, player.pos_y, player.vel_x, player.vel_y, player.angle });
            player.reload_time = 15;
            player.beep.play();
        }
        for (Projectile& projectile : projectiles) {
            projectile.move();
        }
        for (int i = 0; i < projectiles.size(); i++) {
            if (projectiles.at(i).pos_x > WINDOWWIDTH || projectiles.at(i).pos_x < 0 || projectiles.at(i).pos_y > WINDOWHEIGHT || projectiles.at(i).pos_y < 0) {
                projectiles.erase(std::next(projectiles.begin(), i));
            }
        }
        player.reload_time -= 1;
    }

    void draw() override
    {
        player.draw();
        background_image->draw(0, 0, Z_BACKGROUND);
        for (Projectile& projectile : projectiles) {
            projectile.draw();
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
	GameWindow window;
	window.show();
}
