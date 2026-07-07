#pragma once

#include "sprite_component.h"

class AnimatedSpriteComponent : public SpriteComponent
{
public:
	AnimatedSpriteComponent(Entity* entity, int draw_order = 0);
	~AnimatedSpriteComponent();

	void update(float delta_time) override;
	void set_animation_textures(const std::vector<SDL_Texture*>& textures);

	std::vector<SDL_Texture*> animation_textures;
	float current_frame;
	float animation_fps;
};
