#include "SDL2_renderer.h"
#include "glm/glm.hpp"
#include <iostream>

int SDL2_renderer::Init()
{
	int width = 600;
	int height = 400;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL2.0: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	_window = SDL_CreateWindow("Game", 400, 200, width, height, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		fprintf(stderr, "Failed to create SDL2.0 window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr)
	{
		SDL_DestroyWindow(_window);
		fprintf(stderr, "Failed to create SDL2.0 renderer: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	_viewport = glm::vec4(0.0f, 0.0f, width, height);
	return 0;
}

void SDL2_renderer::Clean()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void SDL2_renderer::Render(RendererInData* rendererInData)
{
	HandleEvents();
	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
	SDL_RenderClear(_renderer);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

	//glm::mat4 MVPmatrix = (*_projectionMatrix) * (*_viewMatrix) * _modelMatrices[1] glm* glm::mat4(0.0f, 0.0f, -5.0f);
	for (int i = 0; i < rendererInData->transformOutDataLength; ++i)
	{
		if (!rendererInData->transformOutData[i]._render)
			continue;

		for (int j = 0; j < 8; ++j)
		{
			_pss[j] = glm::project(_points[j], rendererInData->transformOutData[i]._modelMatrix, *rendererInData->projectionMatrix, _viewport);
		}
		SDL_RenderDrawLine(_renderer, _pss[0].x, _pss[0].y, _pss[1].x, _pss[1].y);
		SDL_RenderDrawLine(_renderer, _pss[1].x, _pss[1].y, _pss[2].x, _pss[2].y);
		SDL_RenderDrawLine(_renderer, _pss[2].x, _pss[2].y, _pss[3].x, _pss[3].y);
		SDL_RenderDrawLine(_renderer, _pss[3].x, _pss[3].y, _pss[0].x, _pss[0].y);

		SDL_RenderDrawLine(_renderer, _pss[4].x, _pss[4].y, _pss[5].x, _pss[5].y);
		SDL_RenderDrawLine(_renderer, _pss[5].x, _pss[5].y, _pss[6].x, _pss[6].y);
		SDL_RenderDrawLine(_renderer, _pss[6].x, _pss[6].y, _pss[7].x, _pss[7].y);
		SDL_RenderDrawLine(_renderer, _pss[7].x, _pss[7].y, _pss[4].x, _pss[4].y);

		SDL_RenderDrawLine(_renderer, _pss[0].x, _pss[0].y, _pss[4].x, _pss[4].y);
		SDL_RenderDrawLine(_renderer, _pss[1].x, _pss[1].y, _pss[5].x, _pss[5].y);
		SDL_RenderDrawLine(_renderer, _pss[2].x, _pss[2].y, _pss[6].x, _pss[6].y);
		SDL_RenderDrawLine(_renderer, _pss[3].x, _pss[3].y, _pss[7].x, _pss[7].y);
	}

	SDL_RenderPresent(_renderer);
}

void SDL2_renderer::HandleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{

	}
}
