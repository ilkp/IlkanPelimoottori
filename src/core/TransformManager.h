#pragma once
#include <queue>
#include "glm/glm.hpp"
#include "EntityManager.h"
#include "EntityData.h"

typedef struct TransformData : EntityData
{
	TransformData* _parent = nullptr;
	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	TransformData() {}
	TransformData(TransformData* parent) : _parent(parent) {}

} TransformData;

class TransformManager: public EntityManager
{
public:
	TransformData* _entityData = nullptr;

	void Execute(float deltaTime);
	void Init(uint32_t size);
	~TransformManager();
	void Clean();
	uint32_t Reserve();
	void Release(uint32_t index);
	TransformData* GetEntityData(uint32_t index) const;
};
