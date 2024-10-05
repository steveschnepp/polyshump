#include "usdl.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window *window;
SDL_Renderer *renderer;

int SCREEN_WIDTH = 320;
int SCREEN_HEIGHT = 240;
int FRAME_TIMINGS = 100;
int UPDATE_RATE = 30;
long frame = 0;
int quit = 0;

#define BUTTON_TIMEOUT (60 * 3)
struct controller {
	int buttons[SDL_CONTROLLER_BUTTON_MAX];
};

static
struct controller CONTROLLERS[8];

static
int max(int a, int b)
{
	if (a < b) return b;
	return a;
}

__attribute__((weak))
char *APP_TITLE()
{
	return _(USDL_APPNAME);
}

__attribute__((weak))
void setup(int argc, char *argv[])
{
}

__attribute__((weak))
void update_event(SDL_Event e)
{
}

__attribute__((weak))
void update(uint32_t delta_ms)
{
}

__attribute__((weak))
void draw()
{
}

void cls()
{
	SDL_SetRenderDrawColor(renderer, 16, 16, 16, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRectF(renderer, NULL);
}

static
void emit_timings(uint32_t update_ticks, uint32_t draw_ticks, uint32_t wait_ticks)
{
	static uint32_t update_ticks_acc, draw_ticks_acc, wait_ticks_acc = 0;

	update_ticks_acc += update_ticks;
	draw_ticks_acc += draw_ticks;
	wait_ticks_acc += wait_ticks;

	if (frame % FRAME_TIMINGS)
		return;

	SDL_Log("frame %06lu updated %04u draw %04u wait %04u ms\n", frame, update_ticks_acc, draw_ticks_acc, wait_ticks_acc);
	update_ticks_acc = draw_ticks_acc = wait_ticks_acc = 0;
}

static uint32_t last_frame_tick;
static int fullScreen = 0;

static const
SDL_Scancode SCANCODE_MAPPING[16][SDL_CONTROLLER_BUTTON_MAX] = {
	// LEFT, RIGHT, UP, DOWN, O, X, A, B, L, R
	{SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,
	 SDL_SCANCODE_O, SDL_SCANCODE_P, SDL_SCANCODE_L, SDL_SCANCODE_SEMICOLON,
	 SDL_SCANCODE_PERIOD, SDL_SCANCODE_SLASH,},
	{SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,
	 SDL_SCANCODE_R, SDL_SCANCODE_T, SDL_SCANCODE_F, SDL_SCANCODE_G,
	 SDL_SCANCODE_V, SDL_SCANCODE_B,},
};

static
int is_key_pressed(int controller_id, int button_id)
{
	// Hard coded mapping
	int numkeys;
	const uint8_t *key_state = SDL_GetKeyboardState(&numkeys);
	SDL_Scancode scan_code = SCANCODE_MAPPING[controller_id][button_id];
	if (scan_code == SDL_SCANCODE_UNKNOWN)
		return 0;
	if (scan_code >= numkeys)
		return 0;

	int is_pressed = key_state[scan_code];
	return is_pressed;
}

int btn(int button_id, int controller_id)
{
	return CONTROLLERS[controller_id].buttons[button_id];
}

static
void main_loop()
{
	SDL_Event e;
	// Handle the event stream
	while (SDL_PollEvent(&e) != 0) {
		//User requests quit
		if (e.type == SDL_QUIT) {
			quit = 1;
			return;
		}

		if (e.type == SDL_WINDOWEVENT) {
			switch (e.window.event) {

			default:
				break;
			}
		}

		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				quit = 1;
				return;
			case 'f':
				fullScreen = !fullScreen;
				if (fullScreen) {
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				} else {
					SDL_SetWindowFullscreen(window, 0);
				}

				break;
			}
		}

		update_event(e);
	}

	// Update the button states for the controllers
	for (int controller_id = 0; controller_id < max(SDL_NumJoysticks(), 3); controller_id++) {
		//      SDL_Log("controller_id %d", controller_id);
		//      if (!SDL_IsGameController(controller_id))
		//              continue;
		SDL_GameController *controller = SDL_GameControllerOpen(controller_id);
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
			//      SDL_Log("controller %d", controller_id);
			if (SDL_GameControllerGetButton(controller, i)
			    || is_key_pressed(controller_id, i)) {
				CONTROLLERS[controller_id].buttons[i]++;
			} else {
				CONTROLLERS[controller_id].buttons[i] = 0;
			}

		}
	}

	uint32_t start_frame_tick = SDL_GetTicks();
	uint32_t frame_tick = start_frame_tick - last_frame_tick;
	static int32_t accumulator = 0;

	accumulator += frame_tick;

	// Update logic at fixed UPDATE_RATE rate
	int32_t update_tick_rate = 1000 / UPDATE_RATE;
	while (accumulator >= update_tick_rate) {
		update(update_tick_rate);
		accumulator -= update_tick_rate;
	}

	uint32_t start_draw_tick = SDL_GetTicks();

	// Draw
	{
		draw();
		frame++;
	}

	uint32_t end_draw_tick = SDL_GetTicks();

	SDL_RenderPresent(renderer);

	{
		uint32_t end_sync_tick = SDL_GetTicks();
		uint32_t update_ticks = start_draw_tick - start_frame_tick;
		uint32_t draw_ticks = end_draw_tick - start_draw_tick;
		uint32_t wait_ticks = end_sync_tick - end_draw_tick;
		emit_timings(update_ticks, draw_ticks, wait_ticks);
	}

	last_frame_tick = start_frame_tick;

	return;
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);

	int sdl_flags = 0;
	sdl_flags |= SDL_WINDOW_RESIZABLE;
	sdl_flags |= SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
	char *app_title = APP_TITLE();
	window =
	    SDL_CreateWindow(app_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2,
			     sdl_flags);

	int sdl_renderer_flags = 0;
	sdl_renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, sdl_renderer_flags);

	{
		SDL_RendererInfo info;
		SDL_GetRendererInfo(renderer, &info);
		SDL_Log("renderer %s %d,%d", info.name, info.max_texture_width, info.max_texture_height);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");	// make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_RaiseWindow(window);

	setup(argc, argv);

	SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");

	last_frame_tick = SDL_GetTicks();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop, 0, 1);
#else				// __EMSCRIPTEN__
	while (!quit)
		main_loop();
#endif

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
