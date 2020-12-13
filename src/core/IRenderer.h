#pragma once
#include <cstdint>
#include "TransformManager.h"

class IRenderer
{
public:
	virtual void Init(TransformManager* tm) = 0;
	virtual void Clean() = 0;
	virtual void Render() = 0;
};