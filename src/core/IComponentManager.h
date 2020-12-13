#pragma once
#include <cstdint>

class IComponentManager
{
public:
	IComponentManager() {}
	IComponentManager(uint32_t size) {}
	virtual ~IComponentManager() {}
	virtual void Init(uint32_t size) = 0;
	virtual void Execute(double dt) = 0;
};
