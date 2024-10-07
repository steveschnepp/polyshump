#include "p8sdl.h"

void rect(float x1, float y1, float x2, float y2, int color)
{
	SDL_Color c = VGA_COLORS[color % 16];
	SDL_FRect rec = { x1, y1, x2 - x1, y2 - y1 };

	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawRectF(renderer, &rec);
}

void rectfill(float x1, float y1, float x2, float y2, int color)
{
	SDL_Color c = VGA_COLORS[color % 16];
	SDL_FRect rec = { x1, y1, x2 - x1, y2 - y1 };

	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRectF(renderer, &rec);
}

float _cosf(int i)
{
	return COSF[i % NUM_CIRCLE_EDGES];
}

float _sinf(int i)
{
	return SINF[i % NUM_CIRCLE_EDGES];
}

void circ_line(float x, float y, float r, int color)
{
	SDL_Color c = VGA_COLORS[color % 16];

	SDL_FPoint points[NUM_CIRCLE_EDGES];

	for (int i = 0; i < NUM_CIRCLE_EDGES; i++) {
		points[i].x = x + r * _cosf(i);
		points[i].y = y + r * _sinf(i);
	}

	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLinesF(renderer, points, NUM_CIRCLE_EDGES);
}

float absf(float f)
{
	if (f < 0) return -f;
	return f;
}

void circ_strip(float x, float y, float r, int color)
{
	SDL_Color c = VGA_COLORS[color % 16];

	SDL_Vertex vertices[(NUM_CIRCLE_EDGES + 1) * 6];

	float line_width = .5;
	float r_outer = absf(r + line_width);
	float r_inner = absf(r - line_width);
	for (int i = 0; i < NUM_CIRCLE_EDGES; i++) {
		// First triangle of the strip
		vertices[i * 6].position.x = x + r_inner * _cosf(i);
		vertices[i * 6].position.y = y + r_inner * _sinf(i);
		vertices[i * 6].color = c;

		vertices[i * 6 + 1].position.x = x + r_outer * _cosf(i);
		vertices[i * 6 + 1].position.y = y + r_outer * _sinf(i);
		vertices[i * 6 + 1].color = c;

		vertices[i * 6 + 2].position.x = x + r_outer * _cosf(i + 1);
		vertices[i * 6 + 2].position.y = y + r_outer * _sinf(i + 1);
		vertices[i * 6 + 2].color = c;

		// Second triangle of the strip
		vertices[i * 6 + 3].position.x = x + r_inner * _cosf(i);
		vertices[i * 6 + 3].position.y = y + r_inner * _sinf(i);
		vertices[i * 6 + 3].color = c;

		vertices[i * 6 + 4].position.x = x + r_outer * _cosf(i + 1);
		vertices[i * 6 + 4].position.y = y + r_outer * _sinf(i + 1);
		vertices[i * 6 + 4].color = c;

		vertices[i * 6 + 5].position.x = x + r_inner * _cosf(i + 1);
		vertices[i * 6 + 5].position.y = y + r_inner * _sinf(i + 1);
		vertices[i * 6 + 5].color = c;
	}

	SDL_RenderGeometry(renderer, NULL, vertices, NUM_CIRCLE_EDGES * 6, NULL, 0);
}

void circ(float x, float y, float r, int color)
{
	circ_strip(x, y, r, color);
}

void circfill(float x, float y, float r, int color)
{
	SDL_Color c = VGA_COLORS[color % 16];

	SDL_Vertex vertices[(NUM_CIRCLE_EDGES + 1) * 3];

	// fill the triangles
	SDL_FPoint o = { x, y };
	for (int i = 0; i < NUM_CIRCLE_EDGES; i++) {
		vertices[i * 3].position = o;
		vertices[i * 3].color = c;

		vertices[i * 3 + 1].position.x = x + r * _cosf(i);
		vertices[i * 3 + 1].position.y = y + r * _sinf(i);
		vertices[i * 3 + 1].color = c;

		vertices[i * 3 + 2].position.x = x + r * _cosf(i + 1);
		vertices[i * 3 + 2].position.y = y + r * _sinf(i + 1);
		vertices[i * 3 + 2].color = c;
	}

	SDL_RenderGeometry(renderer, NULL, vertices, NUM_CIRCLE_EDGES * 3, NULL, 0);
}
