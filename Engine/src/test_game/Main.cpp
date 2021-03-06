#define SDL_MAIN_HANDLED
#include "Game.h"
#include <iostream>

int main()
{
	Game game;
	if (game.Init(100) != 0)
		return 1;
	game.Start();
	int exit = 0;
	std::cin >> exit;
	game.SetRunning(false);
	game.gameThread.join();
	return 0;
}