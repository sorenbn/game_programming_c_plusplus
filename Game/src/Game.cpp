#include "game.h"
#include <SDL_image.h>

static bool updating_entities = false;

// testing
static SDL_Surface* sprite_surface;
static SDL_Texture* sprite_texture;

Game::Game() : is_running(false), window(nullptr), renderer(nullptr)
{
	tick_count = 0;
}

bool Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_Image: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Game Programming in C++ (Chapter 1)",
							  SDL_WINDOWPOS_CENTERED, // window pos x
							  SDL_WINDOWPOS_CENTERED, // window pos y
							  WINDOW_SIZE_X,		  // window width
							  WINDOW_SIZE_Y,		  // window height
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

	// texture in-memory, essentially
	sprite_surface = IMG_Load("assets/sprites/test.png");
	// texture on the GPU, essentially
	sprite_texture = SDL_CreateTextureFromSurface(renderer, sprite_surface);

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
	// test
	SDL_DestroyTexture(sprite_texture);

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
	/* ###### ENGINE LOGIC ###### */

	// wait until 16ms has passed since last frame
	// it's essentially doing 'while(SDL_GetTicks() < tick_count + 16)' but with some overflow protection
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), tick_count + 16))
		;

	// calculate current dt in seconds
	float delta_time = (SDL_GetTicks() - tick_count) / 1000.0f;

	// force delta_tima cap if it should exceed some large threshold (like when debugging)
	if (delta_time > 0.05f)
	{
		delta_time = 0.05f;
	}

	// store tick count for the next frame
	tick_count = SDL_GetTicks();

	// update
	updating_entities = true;
	for (Entity* entity : entities)
	{
		entity->update(delta_time);
	}
	updating_entities = false;

	// add potential newly created entities to the list of entities
	for (Entity* pending_entity : pending_entities)
	{
		entities.emplace_back(pending_entity);
	}
	pending_entities.clear();

	// cleanup destroyed entities
	std::vector<Entity*> destroyed_entities;
	for (Entity* entity : entities)
	{
		if (entity->state == Entity::DESTROYED)
		{
			destroyed_entities.emplace_back(entity);
		}
	}

	for (Entity* destroyed_entity : destroyed_entities)
	{
		delete destroyed_entity;
	}
}

void Game::render()
{
	// set draw color for the state machine (like immediate mode)
	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
	// clear the backbuffer with whatecer the current draw color is (set above)
	SDL_RenderClear(renderer);

	// test
	SDL_Rect rect{
		(WINDOW_SIZE_X / 2) - 128,
		(WINDOW_SIZE_Y / 2) - 128,
		256,
		256,
	};

	SDL_RenderCopy(renderer, sprite_texture, NULL, &rect);

	// swap buffers (and present it to the screen)
	SDL_RenderPresent(renderer);
}

void Game::add_entity(Entity* entity)
{
	if (updating_entities)
	{
		pending_entities.emplace_back(entity);
	}
	else
	{
		entities.emplace_back(entity);
	}
}

void Game::remove_entity(Entity* entity)
{
	entity->state = Entity::DESTROYED;
}

SDL_Texture* Game::load_texture(const char* file_name)
{

}