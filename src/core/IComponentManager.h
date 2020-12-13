#pragma once
#include <cstdint>

class IComponentManager
{
public:
	virtual void Init(uint32_t size) = 0;
	virtual void Execute(float dt) = 0;
	virtual void Clean() = 0;
};
