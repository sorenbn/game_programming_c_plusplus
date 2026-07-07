#include "animated_sprite_component.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Entity* entity, int draw_order)
	: SpriteComponent(entity, draw_order),
	animation_textures(NULL),
	current_frame(0),
	animation_fps(24)
{

}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{

}

void AnimatedSpriteComponent::set_animation_textures(const std::vector<SDL_Texture*>& textures)
{
	animation_textures = textures;
	current_frame = 0.0f;
}

void AnimatedSpriteComponent::update(float delta_time)
{
	SpriteComponent::update(delta_time);

	if (animation_textures.size() > 0)
	{
		current_frame += animation_fps * delta_time;

		// wrap the frames if exceeds the size
		while (current_frame >= animation_textures.size())
		{
			current_frame -= animation_textures.size();
		}

		set_texture(animation_textures[static_cast<int>(current_frame)]);
	}
}