#include "Entity.h"

uint32_t Entity::GetEntityIndex(EntityManager* manager)
{
	if (indices.find(manager) == indices.end())
		return 0;
	return indices.at(manager);
}

uint32_t Entity::SetEntityIndex(EntityManager* manager, uint32_t index)
{
	indices[manager] = index;
	return index;
}

void Entity::RemoveEntityIndex(EntityManager* manager)
{
	if (indices.find(manager) != indices.end())
	{
		manager->Release(indices.at(manager));
		indices.erase(manager);
	}
}