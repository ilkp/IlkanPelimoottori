#include "CameraManager.h"

void CameraManager::Execute(float dt)
{
}

void CameraManager::Init(uint32_t size)
{
    _size = size;
    _top = 1;
	_entityData = new CameraData[size + 1];
	_entityData[0]._reserved = true;
}

void CameraManager::Clean()
{
    delete[](_entityData);
}

uint32_t CameraManager::Reserve()
{
	for (uint32_t i = 1; i < _size; ++i)
	{
		if (!_entityData[i]._reserved)
		{
			_entityData[i]._reserved = true;
			if (i == _top)
				++_top;
			return i;
		}
	}
	return 0;
}

void CameraManager::Release(uint32_t index)
{
	if (index == 0)
		return;
	_entityData[index]._reserved = false;
	while (!_entityData[_top - 1]._reserved)
		--_top;
}

CameraData CameraManager::GetCameraData(uint32_t index)
{
	return _entityData[index];
}

void CameraManager::LookAt(uint32_t index, glm::vec3 position, glm::vec3 center, glm::vec3 up)
{
	_entityData[index]._viewMatrix = glm::lookAt(position, center, up);
}
