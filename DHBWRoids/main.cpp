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
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
