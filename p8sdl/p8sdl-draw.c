#include "p8sdl.h"

void rect(float x1, float y1, float x2, float y2, int color) {
	SDL_Color c = VGA_COLORS[color % 16];
	SDL_FRect rec = { x1, y1, x2 - x1, y2 - y1 };

	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawRectF(renderer, &rec);
}

void rectfill(float x1, float y1, float x2, float y2, int color) {
	SDL_Color c = VGA_COLORS[color % 16];
	SDL_FRect rec = { x1, y1, x2 - x1, y2 - y1 };

	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRectF(renderer, &rec);
}

#define NUM_CIRCLE_EDGES 1024

void circ(float x, float y, float r, int color) {
	SDL_Color c = VGA_COLORS[color % 16];

	SDL_FPoint points[NUM_CIRCLE_EDGES * 2];

	for (int i = 0; i < NUM_CIRCLE_EDGES; i ++) {
		points[i * 2].x = x + cosf(M_PI / NUM_CIRCLE_EDGES * i);
		points[i * 2].y = y + sinf(M_PI / NUM_CIRCLE_EDGES * i);

		points[i * 2 + 1].x = x + cosf(M_PI / NUM_CIRCLE_EDGES * (i+1));
		points[i * 2 + 1].y = y + sinf(M_PI / NUM_CIRCLE_EDGES * (i+1));
	}

	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLinesF(renderer, points, NUM_CIRCLE_EDGES * 2);
}

void circfill(float x, float y, float r, int color) {
	SDL_Color c = VGA_COLORS[color % 16];

	SDL_Vertex vertices[(NUM_CIRCLE_EDGES+1) * 3];

	// fill the triangles
	SDL_FPoint o = { x, y };
	for (int i = 0; i < NUM_CIRCLE_EDGES; i ++) {
		vertices[i * 3].position = o;
		vertices[i * 3].color = c;

		vertices[i * 3 + 1].position.x = x + cosf(M_PI / NUM_CIRCLE_EDGES * i);
		vertices[i * 3 + 1].position.y = y + sinf(M_PI / NUM_CIRCLE_EDGES * i);
		vertices[i * 3 + 1].color = c;

		vertices[i * 3 + 2].position.x = x + cosf(M_PI / NUM_CIRCLE_EDGES * (i+1));
		vertices[i * 3 + 2].position.y = y + sinf(M_PI / NUM_CIRCLE_EDGES * (i+1));
		vertices[i * 3 + 2].color = c;
	}

	SDL_RenderGeometry(renderer, NULL, vertices, NUM_CIRCLE_EDGES * 3, NULL, 0);
}
