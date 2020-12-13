#pragma once
#include "IComponentManager.h"
#include "Vector3d.h"

typedef struct TransformData
{
	bool reserved = false;
	Vector3d position;
	Vector3d velocity;
	Vector3d acceleration;
} Transform;

class TransformManager: public IComponentManager
{
public:
	uint32_t size = 0;
	TransformData* data = nullptr;

	TransformManager() {}
	TransformManager(uint32_t size): size(size) { data = new TransformData[size]; }
	~TransformManager() { delete[](data); }
	void Init(uint32_t size) { data = new TransformData[size]; }

	void Execute(double dt)
	{
		for (uint32_t i = 0; i < size; ++i)
		{
			if (data[i].reserved)
			{
				data[i].velocity += data[i].acceleration * dt;
				data[i].position += data[i].velocity * dt;
			}
		}
	}
};

