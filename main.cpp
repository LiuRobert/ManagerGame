#include "Game.h"

int main()
{
	Game::getInstance().init();
	Game::getInstance().run();
	return 0;
}