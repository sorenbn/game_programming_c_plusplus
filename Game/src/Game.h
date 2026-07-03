#pragma once

#include <SDL.h>

class Game
{
public:
	Game();

	bool initialize();
	void run_loop();
	void shutdown();

private:
	void process_input();
	void update_game();
	void render();

	// engine state
	SDL_Window *window;
	SDL_Renderer *renderer;
	Uint32 tick_count;
	bool is_running;
	const int WINDOW_SIZE_X = 1024;
	const int WINDOW_SIZE_Y = 768;
};