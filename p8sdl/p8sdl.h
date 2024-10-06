#include <stdint.h>

#include <SDL.h>

// Needs 2 lines because https://gcc.gnu.org/onlinedocs/gcc-3.4.3/cpp/Stringification.html
#define __STRINGIFY__(x) #x
#define _(x) __STRINGIFY__(x)

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int UPDATE_RATE;

extern int quit;

extern long frame;

extern char *APP_TITLE();

enum draw_keepscreen {
	UDSL_KEEPSCREEN = 0,
	UDSL_CLEARSCREEN = 1,
};

/* PICO-8 style API */

void cls();
void draw();
void update(uint32_t delta_ms);

void spr(int id, float x, float y);

void rect(float x1, float y1, float x2, float y2, int color);
void rectfill(float x1, float y1, float x2, float y2, int color);

void circ(float x, float y, float r, int color);
void circfill(float x, float y, float r, int color);

int btn(int id, int player_id);
int btnp(int id, int player_id);

void print(char *msg, float x, float y, int color);

/* PICO-8 style API extensions */
void spr_zoom(int id, float x, float y, float zx, float zy);

void setup(int argc, char *argv[]);
void screenshot();
