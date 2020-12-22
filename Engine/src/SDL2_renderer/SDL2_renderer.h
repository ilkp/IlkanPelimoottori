#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include "IRenderer.h"

class SDL2_renderer : IRenderer
{
public:
	virtual int Init(int width, int height) override;
	virtual void Clean() override;
	virtual void Render(const CameraData& cameraData) override;
	virtual RenderingData* AddRenderingData(Mesh mesh, Texture texture) override;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _userQuitting = false;
	glm::vec4 _viewport;

	void HandleEvents();
};

