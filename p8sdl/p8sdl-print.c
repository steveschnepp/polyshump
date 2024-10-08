#include "p8sdl.h"

#include "SDL_ttf.h"

TTF_Font *load_font() {
    TTF_Init();
    return  TTF_OpenFont("small_pixel.ttf", 8);
}

void print(char *msg, float x, float y, int color)
{
	static TTF_Font *font = NULL;
	if (!font) font = load_font();

	SDL_Color fg = VGA_COLORS[color];

    SDL_Surface *s = TTF_RenderText_Solid(font, msg, fg);
    if (!s) return;
	SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);

	SDL_FreeSurface(s);	 // We don't need the surface, it has been uploaded to the GPU

    int tw = 0, th = 0;
	SDL_QueryTexture(t, NULL, NULL, &tw, &th);

	float w = 1 * tw;
	float h = 1 * th;

	SDL_FRect dst = { x, y, w, h };
	SDL_RenderCopyF(renderer, t, NULL, &dst);
}
