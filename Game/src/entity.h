#pragma once

#include "vector2.h"

class Entity
{
public:
	enum State
	{
		ENABLED,
		DISABLED,
		DESTROYED,
	};

	// forward declare game here, to avoid importing Game.h
	Entity(class Game* game);
	virtual ~Entity();

	void update(float delta_time);
	void update_components(float delta_time);
	virtual void update_entity(float delta_time);
	
	State state;
	Vector2 position;
	float scale;
};

