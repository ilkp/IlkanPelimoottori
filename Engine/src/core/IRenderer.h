#pragma once
#include <cstdint>
#include "TransformManager.h"

typedef struct RendererInData
{
	uint32_t transformOutDataLength;
	glm::mat4* projectionMatrix;
	glm::mat4* viewMatrix;
	TransformOutData* transformOutData;
} RendererInData;

class IRenderer
{
public:
	virtual int Init() = 0;
	virtual void Clean() = 0;
	virtual void Render(RendererInData* rendererInData) = 0;
};