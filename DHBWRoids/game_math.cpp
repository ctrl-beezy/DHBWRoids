#include "game_math.h"
#include <cstdint>
#include <cmath>

double mathMod(double a, double b)
{
	return (fmod(a,b) + (b * (a < 0)));
}