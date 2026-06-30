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

	SDL_Window *window;
	SDL_Renderer *renderer;
	bool is_running;

	const int WALL_THICKNESS = 15;
};