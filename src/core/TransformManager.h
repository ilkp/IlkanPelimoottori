#pragma once
#include "glm/glm.hpp"
#include "IComponentManager.h"

typedef struct TransformData
{
	bool reserved = false;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
} Transform;

class TransformManager: public IComponentManager
{
public:
	uint32_t _size;
	TransformData* _data;

	void Init(uint32_t size);
	void Execute(float dt);
	void Clean();
};

