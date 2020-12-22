#include "SDL2_renderer.h"
#include "glm/glm.hpp"
#include <iostream>

int SDL2_renderer::Init(int width, int height)
{
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

void SDL2_renderer::Render(const CameraData& cameraData)
{
	HandleEvents();
	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
	SDL_RenderClear(_renderer);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	glm::vec3* projectedPoints = nullptr;

	for (int i = 0; i < _renderingData.size(); ++i)
	{
		for (int j = 0; j < _renderingData[i]->_modelViewData.size(); ++j)
		{
			if (!_renderingData[i]->_modelViewData[j]->_active)
				continue;
			delete[](projectedPoints);
			projectedPoints = new glm::vec3[_renderingData[i]->_mesh._verticesLength];
			for (int k = 0; k < _renderingData[i]->_mesh._verticesLength; ++k)
			{
				projectedPoints[k] = glm::project(_renderingData[i]->_mesh._vertices[k],
					cameraData._viewMatrix * _renderingData[i]->_modelViewData[j]->_modelMatrix,
					cameraData._projectionMatrix,
					_viewport);
			}
			int* triangles = _renderingData[i]->_mesh._triangles;
			for (int k = 0; k < _renderingData[i]->_mesh._trianglesLength; k += 3)
			{
				SDL_RenderDrawLine(_renderer,
					projectedPoints[triangles[k]].x,
					projectedPoints[triangles[k]].y,
					projectedPoints[triangles[k + 1]].x,
					projectedPoints[triangles[k + 1]].y);
				SDL_RenderDrawLine(_renderer,
					projectedPoints[triangles[k + 1]].x,
					projectedPoints[triangles[k + 1]].y,
					projectedPoints[triangles[k + 2]].x,
					projectedPoints[triangles[k + 2]].y);
				SDL_RenderDrawLine(_renderer,
					projectedPoints[triangles[k + 2]].x,
					projectedPoints[triangles[k + 2]].y,
					projectedPoints[triangles[k]].x,
					projectedPoints[triangles[k]].y);
			}
		}
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

RenderingData* SDL2_renderer::AddRenderingData(Mesh mesh, Texture texture)
{
	_renderingData.push_back(new RenderingData(mesh, texture));
	return _renderingData[_renderingData.size() - 1];
}
