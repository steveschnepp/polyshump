#include "p8sdl.h"

float randf(float max)
{
	float r = rand();
	r = r * max / RAND_MAX;
	return r;
}

void draw()
{
	cls();
	for (int i = 0; i < 200; i++) {
		spr_zoom(0, randf(SCREEN_WIDTH), randf(SCREEN_HEIGHT), 0.1, 0.1);
	}
}
