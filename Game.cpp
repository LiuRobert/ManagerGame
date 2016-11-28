#include <SFML/Graphics.hpp>
#include "Game.h"

#include "KeyboardController.h"
#include "LevelLoader.h"
#include "World.h"


Game::~Game()
{
	delete _pWindow;
	delete _pWorld;
	delete _pController;
}

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::init()
{
	_pController = new KeyboardController();
	_pWorld = new World();
	_pWorld->init();
	_pWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "sfml_test");
}

void Game::run()
{
	while (_pWindow->isOpen())
	{
		float deltaTime = _clock.restart().asSeconds();
		std::vector<sf::Event> keyEvents;
		sf::Event event;
		while (_pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_pWindow->close();
		}
		_pController->think();
		_pWorld->think(deltaTime);
		_pWindow->clear(sf::Color(216, 221, 206));
		_pWorld->draw(_pWindow);
		_pWindow->display();
	}
}

World* Game::getWorld()
{
	return _pWorld;
}

KeyboardController* Game::getKeyboardController()
{
	return _pController;
}

sf::RenderWindow * Game::getWindow()
{
	return _pWindow;
}
