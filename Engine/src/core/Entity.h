#pragma once
#include "EntityManager.h"
#include "IRenderer.h"
#include <map>

class Entity
{
public:
	uint32_t GetEntityIndex(EntityManager* manager);
	uint32_t SetEntityIndex(EntityManager* manager, uint32_t index);
	void RemoveEntityIndex(EntityManager* manager);

private:
	std::map<EntityManager*, uint32_t> indices;
	RenderingData* _renderingData;
};