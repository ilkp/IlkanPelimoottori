#include "TransformManager.h"

void TransformManager::Init(uint32_t size)
{
	_size = size;
	_data = new TransformData[size];
}

void TransformManager::Execute(float dt)
{
	for (uint32_t i = 0; i < _size; ++i)
	{
		if (_data[i].reserved)
		{
			_data[i].velocity += _data[i].acceleration * dt;
			_data[i].position += _data[i].velocity * dt;
		}
	}
}

void TransformManager::Clean()
{
	delete[](_data);
}