#pragma once

#include "vector2.h"
#include <vector>

class Entity
{
public:
	enum State
	{
		ENABLED,
		DISABLED,
		DESTROYED,
	};

	Entity(class Game* game);
	virtual ~Entity();

	void update(float delta_time);
	void update_components(float delta_time);
	virtual void update_entity(float delta_time);

	void add_component(class Component* compononent);
	void remove_component(class Component* compononent);
	
	State state;
	Vector2 position;
	float scale;
	float rotation;

	std::vector<class Component*> components;
	class Game* game;
};
