#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

#include "Parent.h"

class Entity;
class EntitySpawner;
class ThinkingEntity;
class WorldGrid;
class WorkOrganizer;

class World:
	public Parent
{
public:
	World();
	~World();
	void init();

	void addEntity(Entity* entity);
	void addEntity(ThinkingEntity* entity);
	void draw(sf::RenderWindow* window);
	WorldGrid* getWorldGrid();
	WorkOrganizer* getWorkOrganizer();
	void removeEntity(Entity* entity) override;
	void requestFocus(sf::RenderWindow* window);
	void think(const float& dt);
	

private:
	sf::View _view;
	std::vector<Entity*> _entities;
	std::vector<ThinkingEntity*> _thinkingEntities;
	WorldGrid* _pWorldgrid;
	WorkOrganizer* _pWorkOrganizer;
};

