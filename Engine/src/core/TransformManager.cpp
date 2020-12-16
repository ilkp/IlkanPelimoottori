#include "TransformManager.h"
#include <glm/gtx/quaternion.hpp>

void TransformManager::Init(uint32_t size)
{
	if (_entityData)
		Clean();
	_size = size;
	_top = 1;
	_entityData = new TransformData[size + 1];
	_outData = new TransformOutData[size + 1];
	_entityData[0]._reserved = true;
}

TransformManager::~TransformManager()
{
	Clean();
}

void TransformManager::Execute(float deltaTime)
{
	for (uint32_t i = 1; i < _top; ++i)
	{
		if (!_entityData[i]._reserved)
			continue;
		_outData[i]._modelMatrix = _entityData[i]._translationMatrix * glm::toMat4(_entityData[i]._quaternion) * _entityData[i]._scaleMatrix;
	}
}

void TransformManager::Clean()
{
	delete[](_entityData);
	delete[](_outData);
}

uint32_t TransformManager::Reserve()
{
	return Reserve(false);
}

uint32_t TransformManager::Reserve(bool resetToIdentity)
{
	for (uint32_t i = 1; i < _size; ++i)
	{
		if (!_entityData[i]._reserved)
		{
			_entityData[i]._reserved = true;
			_outData[i]._render = true;
			if (resetToIdentity)
			{
				_entityData[i]._scaleMatrix = glm::mat4(1.0f);
				_entityData[i]._translationMatrix = glm::mat4(1.0f);
				_entityData[i]._quaternion = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
			}
			if (i == _top)
				++_top;
			return i;
		}
	}
	return 0;
}

uint32_t TransformManager::Reserve(uint32_t nEntities)
{
	if (_top + nEntities > _size)
		return 0;
	uint32_t start = _top;
	for (uint32_t i = _top; i < _top + nEntities; ++i)
	{
		_entityData[i]._reserved = true;
		_outData[i]._render = true;
	}
	_top += nEntities;
	return start;
}

void TransformManager::Release(uint32_t index)
{
	if (index == 0)
		return;
	_entityData[index]._reserved = false;
	_outData[index]._render = false;
	while (!_entityData[_top - 1]._reserved)
		--_top;
}

TransformOutData* TransformManager::GetOutData() { return _outData; }

void TransformManager::SetScale(uint32_t index, glm::vec3 vector)
{
	_entityData[index]._scaleMatrix[0][0] = vector.x;
	_entityData[index]._scaleMatrix[1][1] = vector.y;
	_entityData[index]._scaleMatrix[2][2] = vector.z;
}

void TransformManager::SetScale(uint32_t index, float x, float y, float z)
{
	_entityData[index]._scaleMatrix[0][0] = x;
	_entityData[index]._scaleMatrix[1][1] = y;
	_entityData[index]._scaleMatrix[2][2] = z;
}

void TransformManager::SetScale(uint32_t index, float scale)
{
	_entityData[index]._scaleMatrix[0][0] = scale;
	_entityData[index]._scaleMatrix[1][1] = scale;
	_entityData[index]._scaleMatrix[2][2] = scale;
}

void TransformManager::SetPosition(uint32_t index, glm::vec3 vector)
{
	_entityData[index]._translationMatrix[3][0] = vector.x;
	_entityData[index]._translationMatrix[3][1] = vector.y;
	_entityData[index]._translationMatrix[3][2] = vector.z;
}

void TransformManager::SetPosition(uint32_t index, float x, float y, float z)
{
	_entityData[index]._translationMatrix[3][0] = x;
	_entityData[index]._translationMatrix[3][1] = y;
	_entityData[index]._translationMatrix[3][2] = z;
}

void TransformManager::Translate(uint32_t index, glm::vec3 vector)
{
	_entityData[index]._translationMatrix[3][0] += vector.x;
	_entityData[index]._translationMatrix[3][1] += vector.y;
	_entityData[index]._translationMatrix[3][2] += vector.z;
}

void TransformManager::Translate(uint32_t index, float x, float y, float z)
{
	_entityData[index]._translationMatrix[3][0] += x;
	_entityData[index]._translationMatrix[3][1] += y;
	_entityData[index]._translationMatrix[3][2] += z;
}

void TransformManager::Rotate(uint32_t index, glm::vec3 eulerAngles)
{
	_entityData[index]._quaternion *= glm::quat(eulerAngles);
}

void TransformManager::Rotate(uint32_t index, float x, float y, float z)
{
	_entityData[index]._quaternion *= glm::quat(glm::vec3(x, y, z));
}

