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
