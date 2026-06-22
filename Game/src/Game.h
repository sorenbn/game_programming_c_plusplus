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
	void generate_output();

	SDL_Window* window;
	bool is_running;
};