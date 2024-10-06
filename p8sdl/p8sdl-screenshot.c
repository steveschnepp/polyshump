#include "p8sdl.h"

void screenshot()
{
	static int filenumber = 0;

	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	SDL_Surface *screenshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);

	char filename[256] = { 0 };
	sprintf(filename, "screenshots/file-%d.%s", filenumber, "bmp");
	SDL_SaveBMP(screenshot, filename);
	SDL_FreeSurface(screenshot);
	filenumber++;

	SDL_Log("screenshot in %s (%dx%d)", filename, w, h);
}
