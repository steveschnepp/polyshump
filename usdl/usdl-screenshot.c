#include "usdl.h"

#if SCREENSHOTS_ENABLED

#include "SDL_image.h"

void screenshot()
{
	static int filenumber = 0;
	int w, h;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	SDL_Surface *screenshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);

	char filename[256] = { 0 };
	sprintf(filename, "screenshots/file-%d.png", filenumber);
	IMG_SavePNG(screenshot, filename);
	SDL_FreeSurface(screenshot);
	filenumber++;
}

#else // SCREENSHOTS_ENABLED

void screenshot() {
	SDL_Log("Screenshots are disabled");
}

#endif // SCREENSHOTS_ENABLED