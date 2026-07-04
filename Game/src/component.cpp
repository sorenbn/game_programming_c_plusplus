#include "component.h"
#include "entity.h"

Component::Component(Entity* _entity, int update_order)
	: entity(_entity), update_order(update_order)
{
	entity->add_component(this);
}

Component::~Component()
{
	entity->remove_component(this);
}

void Component::update(float delta_time)
{

}