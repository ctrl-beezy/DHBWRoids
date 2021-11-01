#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <cstdint>
#include "game_math.h"

uint16_t WINDOWWIDTH = 1920;
uint16_t WINDOWHEIGHT = 1080;
double x = WINDOWWIDTH/2;
double y = WINDOWHEIGHT/2;
double r = 0;
class GameWindow : public Gosu::Window
{
public:
<<<<<<< Updated upstream
	Gosu::Image bild;
	GameWindow()
		: Window(WINDOWWIDTH, WINDOWHEIGHT),
		bild("Assets/ship.png")
	{
		set_caption("DHBWRoids");
	}

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{

		r = r - 5 * input().down(Gosu::KB_J);
		r = r + 5 * input().down(Gosu::KB_L);

		x = mathMod(double(x - 5 * input().down(Gosu::KB_A)), WINDOWWIDTH);
		x = int32_t(x + 5 * input().down(Gosu::KB_D))%WINDOWWIDTH;

		y = double(int32_t(y + 5 * input().down(Gosu::KB_S))%WINDOWHEIGHT);
		y = mathMod(double(y - 5 * input().down(Gosu::KB_W)), WINDOWWIDTH);

		bild.draw_rot(x, y, 0.0, r);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
	}
=======
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
            maximum_asteroids++;
        }

        // create new projectiles and play sound, reset reload time
        if (Gosu::Input::down(Gosu::KB_SPACE) && (player.reload_time <= 0)) {
            projectiles.push_back({ player.pos_x, player.pos_y, player.vel_x, player.vel_y, player.angle });
            player.reload_time =  10;   //waiting 167ms for next projectile; (10/60)frames per second
            player.beep.play();         //playing projectile sound
        }
        // call player character movement function
        player.move();
        
        // call projectile movement function for all projectiles
        for (Projectile& projectile : projectiles) {
            projectile.move();
            for (Asteroid& asteroid : asteroids) {
                if (asteroid.got_hit(projectile.pos_x, projectile.pos_y)) {
                    //Asteroid hit
                    player.score += 10;
                    //create two smaller asteroids
                    if (asteroid.size == big) {
                        double rand1 = Gosu::random(-1, 1);     //random for different angle and speed (first split)
                        double rand2 = Gosu::random(-1, 1);
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 6*rand1, 6*rand2, rand1, "Assets/Bilder/asteroid.png", medium});
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 6*rand2, 6*rand1, rand2, "Assets/Bilder/asteroid.png", medium});
                    }
                    if (asteroid.size == medium) {
                        double rand1 = Gosu::random(-1,1);      //random for different angle and speed (second split)
                        double rand2 = Gosu::random(-1,1);
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 7*rand1, 7*rand1, Gosu::random(0,90), "Assets/Bilder/asteroid.png", little});
                        newAsteroids.push_back({ asteroid.pos_x, asteroid.pos_y, 7*rand2, 7*rand2, Gosu::random(0,90), "Assets/Bilder/asteroid.png", little});

                    }
                    projectile.pos_x = -100;
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
        //delete off screen projectiles
        if(projectiles.size() > 0){
            auto i = std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile o) {return (o.pos_x < 0 || o.pos_y < 0 || o.pos_x > WINDOWWIDTH || o.pos_y > WINDOWHEIGHT);});
            if (i != projectiles.end()) {
                projectiles.erase(i);
            }
        }
        for (Asteroid newAsteroid : newAsteroids) {
            asteroids.push_back(newAsteroid);
        }
        //Ship hit?
        for (Asteroid& asteroid : asteroids) {
            if (asteroid.got_hit(player.pos_x, player.pos_y)) {
                //player.pos_x = -100;
            }
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
        for (Asteroid asteroid : asteroids) {
            asteroid.draw();
        }
        for (Projectile projectile : projectiles) {
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
>>>>>>> Stashed changes
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
