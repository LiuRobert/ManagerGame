#pragma once
#include <SFML\Graphics.hpp>
#include "KeyBinder.h"

class World;
class KeyboardController;

class Game
{
public:
	~Game();

	static Game& getInstance();
	void init();
	void run();

	World* getWorld();
	KeyboardController* getKeyboardController();
	sf::RenderWindow* getWindow();

private:
	Game() {};
	Game(Game const&) = delete;
	void operator= (Game const&) = delete;

	sf::Clock _clock;
	sf::RenderWindow* _pWindow;
	KeyBinder* _pKeyBinder;
	KeyboardController* _pController;
	World* _pWorld;
};

