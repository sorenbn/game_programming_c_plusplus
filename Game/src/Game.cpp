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
		SDL_WINDOWPOS_CENTERED,	// window pos x
		SDL_WINDOWPOS_CENTERED,	// window pos y
		1024,					// window width
		768,					// window height
		0);						// window flags

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
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
		generate_output();
	}
}

void Game::shutdown()
{
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

	const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

	if (keyboard_state[SDL_SCANCODE_ESCAPE])
	{
		is_running = false;
	}
}

void Game::update_game()
{

}

void Game::generate_output()
{

}