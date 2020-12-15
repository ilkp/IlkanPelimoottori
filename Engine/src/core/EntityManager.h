#pragma once
#include <cstdint>
#include <queue>
#include "EntityData.h"

class EntityManager
{
public:
	uint32_t _size = 0;

	virtual void Execute(float dt) = 0;
	virtual void Init(uint32_t size) = 0;
	virtual void Clean() = 0;
	virtual uint32_t Reserve() = 0;
	virtual void Release(uint32_t index) = 0;

protected:
	std::queue<uint32_t> _releasedIndices;
};