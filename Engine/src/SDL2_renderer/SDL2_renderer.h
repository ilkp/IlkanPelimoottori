#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include "IRenderer.h"

class SDL2_renderer : IRenderer
{
public:
	virtual int Init() override;
	virtual void Clean() override;
	virtual void Render(RendererInData* rendererInData) override;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _userQuitting = false;

	glm::vec3 _points[8] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, 2.0f),

		glm::vec3(0.0f, 2.0f, 0.0f),
		glm::vec3(2.0f, 2.0f, 0.0f),
		glm::vec3(2.0f, 2.0f, 2.0f),
		glm::vec3(0.0f, 2.0f, 2.0f)
	};

	glm::vec3 _pss[8];

	glm::vec4 _viewport;

	void HandleEvents();
};

