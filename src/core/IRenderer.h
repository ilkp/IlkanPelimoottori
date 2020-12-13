#pragma once
#include <cstdint>

class IRenderer
{
public:
	virtual bool Init(uint64_t* models) = 0;
	virtual void Clean() = 0;
	virtual void Render() = 0;
};