#include "sprite_component.h"
#include "math.h"
#include "game.h"

SpriteComponent::SpriteComponent(Entity* _entity, int _draw_order)
	: Component(_entity), 
	texture(nullptr), 
	draw_order(_draw_order),
	texture_width(0),
	texture_height(0)
{
	entity->game->add_sprite(this);
}

SpriteComponent::~SpriteComponent()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}

	entity->game->remove_sprite(this);
}

void SpriteComponent::draw(SDL_Renderer* _renderer)
{
	if (texture)
	{
		SDL_Rect rect;
		rect.w = static_cast<int>(texture_width * entity->scale);
		rect.h = static_cast<int>(texture_height * entity->scale);

		rect.x = static_cast<int>(entity->position.x - rect.w / 2);
		rect.y = static_cast<int>(entity->position.y - rect.h / 2);

		SDL_RenderCopyEx(
			_renderer,
			texture,
			nullptr,
			&rect,
			entity->rotation * RAD_TO_DEG,
			nullptr,
			SDL_FLIP_NONE);
	}
}

void SpriteComponent::set_texture(SDL_Texture* _texture)
{
	texture = _texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);
}