// The complete Gosu library.
#include <Gosu/Gosu.hpp>
// Makes life a little easier when compiling the game in Visual C++.
#include <Gosu/AutoLink.hpp>

#include <cmath>
#include <cstdlib>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include "game_math.h"
#include "GameObjects.h"

const uint16_t WINDOWWIDTH = 1280;
const uint16_t WINDOWHEIGHT = 720;


class GameWindow : public Gosu::Window
{
    std::unique_ptr<Gosu::Image> background_image;
    std::vector<Projectile> projectiles;
    Player player = { "media/Starfighter.bmp", 0.96, 0.7, 0};

public:
    GameWindow()
        : Window(WINDOWWIDTH, WINDOWHEIGHT)
    {
        set_caption("DHBWROIDS");

        std::string filename = "Assets/space.png";
        background_image.reset(new Gosu::Image(filename, Gosu::IF_TILEABLE));

        player.warp(WINDOWWIDTH/2, WINDOWHEIGHT/2);
    }

    void update() override
    {
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
        if (Gosu::Input::down(Gosu::KB_SPACE)) {
            projectiles.push_back();
        }
    }

    void draw()
    {
        player.draw();
        background_image->draw(0, 0);
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

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
