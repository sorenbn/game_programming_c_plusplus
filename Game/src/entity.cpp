#include "entity.h"
#include "component.h"
#include "game.h"
#include "vector2.h"
#include "animated_sprite_component.h"

Entity::Entity(Game* _game)
	: state(ENABLED),
	position(vector2_zero()),
	scale(1),
	rotation(0),
	game(_game)
{
	game->add_entity(this);

	// test code
	position = { 512, 512};

	AnimatedSpriteComponent* animation = new AnimatedSpriteComponent(this);
	animation->animation_fps = 6;
	std::vector<SDL_Texture*> animation_textures = {
		game->load_texture("assets/sprites/k1.png"),
		game->load_texture("assets/sprites/k2.png"),
		game->load_texture("assets/sprites/k3.png"),
		game->load_texture("assets/sprites/k4.png"),
		game->load_texture("assets/sprites/k5.png"),
		game->load_texture("assets/sprites/k6.png"),
		game->load_texture("assets/sprites/k7.png"),
		game->load_texture("assets/sprites/k8.png"),
	};
	animation->set_animation_textures(animation_textures);
}

Entity::~Entity()
{
	game->remove_entity(this);

	while (!components.empty())
	{
		// delete from the back of the list
		delete components.back();
	}
}

void Entity::update(float delta_time)
{
	if (state == ENABLED)
	{
		update_components(delta_time);
		update_entity(delta_time);
	}
}

void Entity::update_components(float delta_time)
{
	for (Component* component : components)
	{
		component->update(delta_time);
	}
}

void Entity::update_entity(float delta_time)
{
}

void Entity::add_component(Component* component)
{
	int order = component->update_order;
	auto iterator = components.begin();

	for (; iterator != components.end(); ++iterator)
	{
		if (order < (*iterator)->update_order)
		{
			break;
		}
	}

	components.insert(iterator, component);
}

void Entity::remove_component(Component* component)
{
	auto iterator = std::find(components.begin(), components.end(), component);

	if (iterator != components.end())
	{
		components.erase(iterator);
	}
}