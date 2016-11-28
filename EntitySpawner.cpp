#include "EntitySpawner.h"

#include "Game.h"
#include "GridCoord.h"
#include "KeyboardController.h"
#include "Wall.h"
#include "Worker.h"
#include "World.h"
#include "WorldGrid.h"
#include "WorkOrganizer.h"



EntitySpawner::EntitySpawner()
{
}

EntitySpawner::~EntitySpawner()
{
}

void EntitySpawner::init(const float & gridSize)
{
	_gridSize = gridSize;
	KeyboardController* k = Game::getInstance().getKeyboardController();
	k->addKeyBind({ { sf::Keyboard::E, KeyboardController::KeyState::onKeyDown } }, Operations::SpawnWorker, this);
	k->addKeyBind({ { sf::Keyboard::W, KeyboardController::KeyState::keyPressed } }, Operations::SpawnWall, this);
	k->addKeyBind({ { sf::Keyboard::R, KeyboardController::KeyState::onKeyDown } }, Operations::ShowCoords, this);
	k->addKeyBind({ { sf::Keyboard::T, KeyboardController::KeyState::keyPressed } }, Operations::RemoveEntity, this);
}


void EntitySpawner::control(const long& operation)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*Game::getInstance().getWindow());
	int x = mousePos.x / _gridSize;
	int y = mousePos.y / _gridSize;
	switch (operation)
	{
	case Operations::SpawnWall:
		spawnWall(x, y);
		break;

	case Operations::SpawnWorker:
		spawnWorker(x, y);
		break;

	case Operations::ShowCoords:
		std::cout <<"Mouse x:" <<mousePos.x <<" y:" <<mousePos.y <<std::endl;
		std::cout << "Grid x:" << mousePos.x / _gridSize << " y:" << mousePos.y / _gridSize << std::endl;
		break;

	case Operations::RemoveEntity:
		removeEntity(x, y);
		break;
	}
}

void EntitySpawner::spawnWall(const int & gridX, const int & gridY)
{
	World* world = Game::getInstance().getWorld();
	WorldGrid* wg = world->getWorldGrid();
	if (wg->insideMap(gridX, gridY))
	{
		if (wg->getEntity(gridX, gridY) == nullptr)
		{
			std::cout << "Spawning Wall" << std::endl;
			Wall* wall = new Wall(wg->getGridSize() * gridX, wg->getGridSize() * gridY);
			world->addEntity(wall);
			world->getWorldGrid()->addEntity(gridX, gridY, wall);
		}
	}
}

void EntitySpawner::spawnWorker(const int& gridX, const int& gridY)
{
	World* world = Game::getInstance().getWorld();
	WorldGrid* wg = world->getWorldGrid();
	if (wg->insideMap(gridX, gridY))
	{
		if (wg->getEntity(gridX, gridY) == nullptr)
		{
			std::cout << "Spawning worker" << std::endl;
			Worker* worker = new Worker(GridCoord(gridX, gridY));
			world->addEntity(worker);
			world->getWorldGrid()->addEntity(gridX, gridY, worker);
			world->getWorkOrganizer()->addWorker(worker);
		}
	}
}

void EntitySpawner::removeEntity(const int & gridX, const int & gridY)
{
	World* world = Game::getInstance().getWorld();
	WorldGrid* wg = world->getWorldGrid();
	if (wg->insideMap(gridX, gridY))
	{
		Entity* e = wg->getEntity(gridX, gridY);
		if (e != nullptr)
			delete e;
	}
}
