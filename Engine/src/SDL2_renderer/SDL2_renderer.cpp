#include "SDL2_renderer.h"

int SDL2_renderer::Init(TransformManager* transformManager)
{
	_transformManager = transformManager;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL2.0: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	_window = SDL_CreateWindow("Game", 800, 400, 600, 400, SDL_WINDOW_SHOWN);
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

	return 0;
}

void SDL2_renderer::Clean()
{
}

void SDL2_renderer::Render()
{
}
