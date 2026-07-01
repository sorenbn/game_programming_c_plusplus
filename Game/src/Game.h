#pragma once

#include <SDL.h>

struct Vector2
{
	float x;
	float y;
};

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

	// actual game state
	const int THICKNESS = 15;
	const int PADDLE_HEIGHT = 100;
	const float PADDLE_SPEED = 300.0f;
	Vector2 paddle_pos;
	Vector2 ball_pos;
	int paddle_direction;
};