#include "KeyBinder.h"

#include "EntitySpawner.h"
#include "Game.h"
#include "KeyboardController.h"
#include "Order.h"
#include "WorkOrganizer.h"
#include "World.h"


KeyBinder::KeyBinder()
{
}

KeyBinder::~KeyBinder()
{
}

void KeyBinder::init(const float& gridSize)
{
	_gridSize = gridSize;
	KeyboardController* k = Game::getInstance().getKeyboardController();
	k->addKeyBind({ { sf::Keyboard::Q, KeyboardController::KeyState::onKeyDown } }, Operations::SpawnWorker, this);
	k->addKeyBind({ { sf::Keyboard::W, KeyboardController::KeyState::keyPressed } }, Operations::SpawnWall, this);
	k->addKeyBind({ { sf::Keyboard::E, KeyboardController::KeyState::onKeyDown } }, Operations::ShowCoords, this);
	k->addKeyBind({ { sf::Keyboard::R, KeyboardController::KeyState::keyPressed } }, Operations::RemoveEntity, this);
	k->addKeyBind({ { sf::Keyboard::T, KeyboardController::KeyState::onKeyDown } }, Operations::MoveOrder, this);
}

void KeyBinder::control(const long& operation)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*Game::getInstance().getWindow());
	int x = mousePos.x / _gridSize;
	int y = mousePos.y / _gridSize;
	switch (operation)
	{
	case Operations::SpawnWall:
		EntitySpawner::spawnWall(x, y);
		break;

	case Operations::SpawnWorker:
		EntitySpawner::spawnWorker(x, y);
		break;

	case Operations::ShowCoords:
		std::cout << "Mouse x:" << mousePos.x << " y:" << mousePos.y << std::endl;
		std::cout << "Grid x:" << mousePos.x / _gridSize << " y:" << mousePos.y / _gridSize << std::endl;
		break;

	case Operations::RemoveEntity:
		EntitySpawner::removeEntity(x, y);
		break;

	case Operations::MoveOrder:
		Game::getInstance().getWorld()->getWorkOrganizer()->addOrder(Order({ { Order::Move, {x, y} } }, 1));
		break;
	}
}
