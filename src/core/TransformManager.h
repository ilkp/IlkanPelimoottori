#pragma once
#include <queue>
#include "glm/glm.hpp"
#include "EntityManager.h"

typedef struct TransformData
{
	TransformData* _parent = nullptr;
	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	TransformData() {}
	TransformData(TransformData* parent) : _parent(parent) {}

} TransformData;

class TransformManager: public EntityManager<TransformData>
{
public:
	void Execute(float dt)
	{
		for (uint32_t i = 0; i < _size; ++i)
		{
			if (_entities[i]._reserved)
			{
				_entities[i]._data._velocity += _entities[i]._data._acceleration * dt;
				_entities[i]._data._position += _entities[i]._data._velocity * dt;
			}
		}
	}
};

