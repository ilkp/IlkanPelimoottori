#include "Game.h"

int main()
{
	Game game(2);
	game.Start();
	int exit = 0;
	std::cin >> exit;
	game.SetRunning(false);
	game.gameThread.join();
	return 0;
}