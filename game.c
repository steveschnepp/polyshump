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

	if (0)
	for (int i = 0; i < 20; i++) {
		spr_zoom(0, randf(SCREEN_WIDTH), randf(SCREEN_HEIGHT), 0.1, 0.1);
	}

	if (0)
	for (int i = 0; i < 20; i++) {
		rectfill(
				randf(SCREEN_WIDTH), randf(SCREEN_HEIGHT),
				randf(SCREEN_WIDTH), randf(SCREEN_HEIGHT),
			i);
	}

	for (int i = 0; i < 20; i++) {
		circ(
				randf(SCREEN_WIDTH), randf(SCREEN_HEIGHT),
				randf(64),
			i);
		circfill(
				randf(SCREEN_WIDTH), randf(SCREEN_HEIGHT),
				randf(64),
			i);
	}
}
