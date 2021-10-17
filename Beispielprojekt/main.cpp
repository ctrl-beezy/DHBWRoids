#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

double x = 0;
double y = 0;
double r = 0;
class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(1048, 720),
		bild("rakete.png")
	{
		set_caption("DHBWRoids");
	}

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{

		r = r - 5 * input().down(Gosu::KB_J);
		r = r + 5 * input().down(Gosu::KB_K);

		x = x - 5 * input().down(Gosu::KB_A);
		x = x + 5 * input().down(Gosu::KB_D);

		y = y - 5 * input().down(Gosu::KB_W);
		y = y + 5 * input().down(Gosu::KB_S);

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
