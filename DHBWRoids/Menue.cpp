/*#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

extern  uint16_t WINDOWWIDTH;
extern	uint16_t WINDOWHEIGHT;

public: GameWindow() :Window(WINDOWWIDTH, WINDOWHEIGHT, true);

void menue() override
{
	if(spielen)
	{
		return;
	}
	else
	{
		graphics().draw_quad(
			(WINDOWWIDTH / 3), (WINDOWHEIGHT / 3), Gosu::Color::GREEN,
			((WINDOWWIDTH / 3) * 2), (WINDOWHEIGHT / 3), Gosu::Color::GREEN,
			((WINDOWWIDTH / 3) * 2), ((WINDOWHEIGHT / 3) * 2), Gosu::Color::GREEN,
			(WINDOWWIDTH / 3), ((WINDOWHEIGHT / 3) * 2), Gosu::Color::GREEN, 0.0);

		graphics().draw_quad(
			(WINDOWWIDTH / 3), ((WINDOWHEIGHT / 3) + 200), Gosu::Color::BLUE,
			((WINDOWWIDTH / 3) * 2), ((WINDOWHEIGHT / 3) + 200), Gosu::Color::BLUE,
			((WINDOWWIDTH / 3) * 2), (((WINDOWHEIGHT / 3) * 2) + 200), Gosu::Color::BLUE,
			(WINDOWWIDTH / 3), (((WINDOWHEIGHT / 3) * 2) + 200), Gosu::Color::BLUE, 0.0);

		text.draw_text("Spielen", 310, 270, 0, 10, 10);
		text.draw_text("Zur�ck", 290, 470, 0, 10, 10);
		text.draw_text(highscore_txt, 250, 120, 0, 5, 5);
		text.draw_text("DHBWRoids", 250, 20, 0, 10, 10);
	}
}*/