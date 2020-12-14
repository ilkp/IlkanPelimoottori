#pragma once
#include <cstdint>
#include "TransformManager.h"

class IRenderer
{
public:
	virtual int Init(TransformManager* transformManager) = 0;
	virtual void Clean() = 0;
	virtual void Render() = 0;
};