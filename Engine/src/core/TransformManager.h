#pragma once
#include <queue>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "EntityManager.h"
#include "EntityData.h"

typedef struct TransformData : EntityData
{
	TransformData* _parent = nullptr;
	glm::mat4 _scaleMatrix = glm::mat4(1.0f);
	glm::mat4 _translationMatrix = glm::mat4(1.0f);
	glm::quat _quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
} TransformData;

typedef struct TransformOutData
{
	bool _render = false;
	glm::mat4 _modelMatrix;
} TransformOutData;

class TransformManager : public EntityManager
{
public:
	void Init(uint32_t size);
	~TransformManager();
	void Execute(float deltaTime);
	void Clean();
	uint32_t Reserve();
	uint32_t Reserve(bool resetToIdentity);
	void Release(uint32_t index);
	TransformOutData* GetOutData();
	glm::mat4* GetProjectionMatrix();
	glm::mat4* GetViewMatrix();

	void SetScale(uint32_t index, glm::vec3 vector);
	void SetScale(uint32_t index, float x, float y, float z);
	void SetScale(uint32_t index, float scale);
	void SetPosition(uint32_t index, glm::vec3 vector);
	void SetPosition(uint32_t index, float x, float y, float z);
	void Translate(uint32_t index, glm::vec3 vector);
	void Translate(uint32_t index, float x, float y, float z);
	void Rotate(uint32_t index, glm::vec3 vector);
	void Rotate(uint32_t index, float x, float y, float z);

private:
	TransformData* _entityData = nullptr;
	TransformOutData* _outData = nullptr;
	glm::mat4 _projectionMatrix = glm::perspective(
		glm::radians(45.0f),
		4.0f / 3.0f,
		0.1f,
		100.0f);
	glm::mat4 _viewMatrix = glm::lookAt(
		glm::vec3(4.0f, 3.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
};
