#pragma once
#include <cstdint>
#include "TransformManager.h"
#include "CameraManager.h"

typedef struct RendererInData
{
	uint32_t transformOutDataLength;
	TransformOutData* transformOutData;
	CameraData cameraData;
} RendererInData;

class IRenderer
{
public:
	virtual int Init() = 0;
	virtual void Clean() = 0;
	virtual void Render(RendererInData* rendererInData) = 0;
};