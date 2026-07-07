#pragma once

#include "component.h"
#include "entity.h"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent(Entity* _entity, int draw_order);
	~SpriteComponent();

	virtual void draw(SDL_Renderer* renderer);
	virtual void set_texture(SDL_Texture* texture);

	SDL_Texture* texture;

	int draw_order;
	int texture_width;
	int texture_height;
};
