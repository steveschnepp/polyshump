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

void cls();
void draw();
void update(uint32_t delta_ms);
void setup(int argc, char *argv[]);

int btn(int id, int player_id);
int btnp(int id, int player_id);

void screenshot();

void spr(int id, float x, float y);
void spr_zoom(int id, float x, float y, float zx, float zy);