#pragma once

class Component
{
public:
	Component(class Entity* entity, int update_order = 0);
	virtual ~Component();

	virtual void update(float delta_time);
	
	class Entity* entity;
	int update_order;
};
