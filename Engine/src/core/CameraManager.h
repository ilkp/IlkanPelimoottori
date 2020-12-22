#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "EntityManager.h"
#include "EntityData.h"

typedef struct CameraData : EntityData
{
	glm::mat4 _projectionMatrix = glm::perspective(
		glm::radians(45.0f),
		4.0f / 3.0f,
		0.1f,
		100.0f);
	glm::mat4 _viewMatrix = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
} CameraData;

class CameraManager : EntityManager
{
public:
	virtual void Execute(float dt) override;
	virtual void Init(uint32_t size) override;
	virtual void Clean() override;
	virtual uint32_t Reserve() override;
	virtual void Release(uint32_t index) override;
	CameraData GetCameraData(uint32_t index);
	void LookAt(uint32_t index, glm::vec3 position, glm::vec3 center, glm::vec3 up);

private:
	CameraData* _entityData;
};

