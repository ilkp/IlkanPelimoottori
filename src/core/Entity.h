#pragma once
#include "EntityManager.h"
#include "EntityData.h"
#include<map>

class Entity
{
public:
	uint32_t GetEntityIndex(EntityManager* manager)
	{
		if (indices.find(manager) == indices.end())
			return 0;
		return indices.at(manager);
	}

	uint32_t SetEntityIndex(EntityManager* manager, uint32_t index)
	{
		indices[manager] = index;
		return index;
	}

	void RemoveEntityIndex(EntityManager* manager)
	{
		if (indices.find(manager) != indices.end())
		{
			manager->Release(indices.at(manager));
			indices.erase(manager);
		}
	}

private:
	std::map<EntityManager*, uint32_t> indices;
};