#pragma once
#include <SDL.h>
#include "IRenderer.h"

class SDL2_renderer : IRenderer
{
public:
	virtual int Init(TransformManager* transformManager) override;
	virtual void Clean() override;
	virtual void Render() override;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	TransformManager* _transformManager;
};

