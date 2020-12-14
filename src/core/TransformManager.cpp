#include "TransformManager.h"

void TransformManager::Execute(float deltaTime)
{
	for (uint32_t i = 1; i < _top; ++i)
	{
		if (_entityData[i]._reserved)
		{
			_entityData[i]._velocity += _entityData[i]._acceleration * deltaTime;
			_entityData[i]._position += _entityData[i]._velocity * deltaTime;
		}
	}
}

void TransformManager::Init(uint32_t size)
{
	if (_entityData)
		Clean();
	_size = size;
	_entityData = new TransformData[size];
	_entityData[0]._reserved = true;
}

TransformManager::~TransformManager()
{
	Clean();
}

void TransformManager::Clean()
{
	delete[](_entityData);
}

uint32_t TransformManager::Reserve()
{
	for (uint32_t i = 0; i < _size; ++i)
	{
		if (!_entityData[i]._reserved)
		{
			_entityData[i]._reserved = true;
			return i;
		}
	}
	return 0;
}

void TransformManager::Release(uint32_t index)
{
	_entityData[index]._reserved = false;
}

TransformData* TransformManager::GetEntityData(uint32_t index) const
{
	return &_entityData[index];
}
