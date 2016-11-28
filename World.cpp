#include "World.h"

#include "Entity.h"
#include "EntitySpawner.h"
#include "ThinkingEntity.h"
#include "WorldGrid.h"
#include "WorkOrganizer.h"
#include "Utils.h"

World::World()
{
	_pWorldgrid = new WorldGrid();
	_pEntitySpawner = new EntitySpawner();
	_pWorkOrganizer = new WorkOrganizer();
}

World::~World()
{
	std::vector<Entity*> temp = _entities;
	for (size_t i = 0; i < temp.size(); i++)
		delete temp[i];

	delete _pWorldgrid;
	delete _pEntitySpawner;
	delete _pWorkOrganizer;
}

void World::init()
{
	float gridSize = 24.0f;
	_pEntitySpawner->init(gridSize);
	_pWorldgrid->init(32, 24, gridSize);
}


void World::addEntity(Entity* entity)
{
	_entities.push_back(entity);
	entity->addParent(this);
	//std::cout << "Adding Entity" << std::endl;
}

void World::addEntity(ThinkingEntity * entity)
{
	_entities.push_back(entity);
	_thinkingEntities.push_back(entity);
	entity->addParent(this);
	//std::cout << "Adding thinking Entity" << std::endl;
}

void World::draw(sf::RenderWindow * window)
{
	for (size_t i = 0, size = _entities.size(); i < size; i++)
	{
		_entities[i]->draw(window);
	}
}

WorldGrid * World::getWorldGrid()
{
	return _pWorldgrid;
}

WorkOrganizer* World::getWorkOrganizer()
{
	return _pWorkOrganizer;
}

void World::removeEntity(Entity * entity)
{
	Utils::remove(_entities, entity);
	Utils::remove(_thinkingEntities, entity);
}

void World::requestFocus(sf::RenderWindow * window)
{
	window->setView(_view);
}

void World::think(const float& dt)
{
	for (size_t i = 0, size = _thinkingEntities.size(); i < size; i++)
	{
		_thinkingEntities[i]->think(dt);
	}
}
