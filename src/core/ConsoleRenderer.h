#pragma once
#include "IRenderer.h"

class ConsoleRenderer : IRenderer
{
public:
	virtual void Clean() override;
	virtual void Render() override;
	virtual void Init(TransformManager* tm) override;

private:
	TransformManager* _tm;
};

