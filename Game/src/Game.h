#pragma once

#include <vector>
#include <SDL.h>
#include "entity.h"
#include "sprite_component.h"

class Game
{
public:
	Game();

	bool initialize();
	void run_loop();
	void shutdown();
	void process_input();
	void update_game();
	void render();

	void add_entity(Entity* entity);
	void remove_entity(Entity* entity);

	SDL_Texture* load_texture(const char* file_name);

	void add_sprite(SpriteComponent* sprite);

	// engine state
	const int WINDOW_SIZE_X = 1280;
	const int WINDOW_SIZE_Y = 720;
	bool is_running;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Uint32 tick_count;

	std::vector<Entity*> entities;
	std::vector<Entity*> pending_entities;
	std::vector<Entity*> destroyed_entities;
};