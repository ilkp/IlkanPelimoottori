#pragma once
#include <vector>
#include "TransformManager.h"
#include "CameraManager.h"
#include "Mesh.h"
#include "Texture.h"

typedef struct RenderingData
{
	Mesh _mesh;
	Texture _texture;
	std::vector<TransformOutData*> _modelViewData;

	RenderingData(Mesh mesh, Texture texture)
	{
		_mesh = mesh;
		_texture = texture;
	}
};

class IRenderer
{
public:
	virtual int Init(int width, int height) = 0;
	virtual void Clean() = 0;
	virtual void Render(const CameraData& cameraData) = 0;
	virtual RenderingData* AddRenderingData(Mesh mesh, Texture texture) = 0;

protected:
	std::vector<RenderingData*> _renderingData;
};