#include "Game.h"

Game::Game()
	: is_running(false),
	  window(nullptr)
{
}

bool Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Game Programming in C++ (Chapter 1)",
							  SDL_WINDOWPOS_CENTERED, // window pos x
							  SDL_WINDOWPOS_CENTERED, // window pos y
							  1024,					  // window width
							  768,					  // window height
							  0);					  // window flags

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	is_running = true;
	return true;
}

void Game::run_loop()
{
	while (is_running)
	{
		process_input();
		update_game();
		render();
	}
}

void Game::shutdown()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::process_input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			is_running = false;
			break;
		}
	}

	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	if (keyboard_state[SDL_SCANCODE_ESCAPE])
	{
		is_running = false;
	}
}

void Game::update_game()
{
}

void Game::render()
{
	// set draw color for the state machine (like immediate mode)
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	// clear the backbuffer with whatecer the current draw color is (set above)
	SDL_RenderClear(renderer);

	// draw wall
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect wall{
		0,
		0,
		1024,
		WALL_THICKNESS};
	SDL_RenderFillRect(renderer, &wall);

	// swap buffers (and present it to the screen)
	SDL_RenderPresent(renderer);
}