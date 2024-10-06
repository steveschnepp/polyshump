#include "p8sdl.h"

#define MAX_SPRITES 256
SDL_Texture *sprites[MAX_SPRITES];

void load_spr(int id)
{
	if (id >= MAX_SPRITES) return;

	SDL_Texture *t = sprites[id];
	if (t) return;

	char filename[4096] = { 0 };
	sprintf(filename, "sprite-%d.bmp", id);

	SDL_Surface *s = SDL_LoadBMP(filename);
	if (!s) return;

	t = SDL_CreateTextureFromSurface(renderer, s);
	SDL_FreeSurface(s);	// We don't need the surface, it has been uploaded to the GPU

	sprites[id] = t;
}

void spr_zoom(int id, float x, float y, float zx, float zy)
{
	load_spr(id);

	SDL_Texture *t = sprites[id];
	if (!t) return;

	int tw = 0, th = 0;
	SDL_QueryTexture(t, NULL, NULL, &tw, &th);

	float w = zx * tw;
	float h = zy * th;

	SDL_FRect dst = { x, y, w, h };
	SDL_RenderCopyF(renderer, t, NULL, &dst);
}

void spr(int id, float x, float y)
{
	spr_zoom(id, x, y, 1, 1);
}
