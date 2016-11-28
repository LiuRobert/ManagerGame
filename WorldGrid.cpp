#include "WorldGrid.h"

#include "Entity.h"
#include "Node.h"
#include "Utils.h"


#include "Game.h"
#include "World.h"


WorldGrid::WorldGrid() : _distanceStraight(1.0), _distanceDiagonal(1.41)
{
	_pEdgeWall = new Entity();
}

WorldGrid::~WorldGrid()
{
}

void WorldGrid::init(const int & worldWidth, const int & worldHeight, const float & gridSize)
{
	_worldSizeX = worldWidth + 2;
	_worldSizeY = worldHeight + 2;
	_gridSize = gridSize;
	_map = new Node[_worldSizeX * _worldSizeY];
	for (int x = 0; x < _worldSizeX; x++)
	{
		for (int y = 0; y < _worldSizeY; y++)
		{
			_map[key(x, y)].x = x;
			_map[key(x, y)].y = y;
			if (x == 0 || y == 0 || x + 1 == _worldSizeX || y + 1 == _worldSizeY)
				_map[key(x, y)].entity = _pEdgeWall;
		}
	}
}

void WorldGrid::addEntity(const int & x, const int & y, Entity * entity)
{
	checkInsideMap(x, y);
	setEntity(x, y, entity);
	entity->addParent(this);
}

Entity* WorldGrid::getEntity(const int& x, const int& y)
{
	checkInsideMap(x, y);
	return _map[key(x, y)].entity;
}

float WorldGrid::getGridSize()
{
	return _gridSize;
}

std::vector<GridCoord> WorldGrid::getPath(const GridCoord& from, const GridCoord& to)
{
	/*
	sf::RenderWindow* window = Game::getInstance().getWindow();
	sf::RectangleShape blueshape(sf::Vector2f(_gridSize, _gridSize));
	blueshape.setFillColor(sf::Color::Blue);
	sf::RectangleShape greenshape(sf::Vector2f(_gridSize, _gridSize));
	greenshape.setFillColor(sf::Color(190, 226, 195));
	*/
	std::vector<GridCoord> result;
	Node* start = &_map[key(from.x, from.y)];
	Node* goal = &_map[key(to.x, to.y)];
	start->distanceGoal = sqrt(pow(start->x - goal->x, 2.0) + pow(start->y - goal->y, 2.0));
	start->distanceTraveled = 0.0;
	start->distanceTotal = start->distanceGoal;
	start->next = nullptr;
	start->prev = nullptr;
	Node* openSet = start;
	Node* closedSet = nullptr;

	while (openSet != nullptr)
	{
		Node* node = openSet;
		openSet = node->next;
		if (openSet != nullptr)
			openSet->prev = nullptr;

		closedSet = node->insert(closedSet);
		node->evaluated = true;
		/*
		Node* current = openSet;
		while (current != nullptr)
		{
			greenshape.setPosition(current->x * _gridSize, current->y * _gridSize);
			window->draw(greenshape);
			current = current->next;
		}
		blueshape.setPosition(node->x * _gridSize, node->y * _gridSize);
		window->draw(blueshape);
		*/
		if (node == goal)
		{
			while (openSet != nullptr)
			{
				openSet->reset();
				openSet = openSet->next;
			}

			while (closedSet != nullptr)
			{
				closedSet->reset();
				closedSet = closedSet->next;
			}

			while (node != start)
			{
				result.push_back({ node->x, node->y });
				node = node->parent;
			}
			return result;
		}

		Node* right = &_map[key(node->x + 1, node->y)];
		if (right->entity == nullptr && !right->evaluated)
			addToSet(openSet, goal, node, right, _distanceStraight);

		Node* down = &_map[key(node->x, node->y + 1)];
		if (down->entity == nullptr && !down->evaluated)
			addToSet(openSet, goal, node, down, _distanceStraight);

		Node* left = &_map[key(node->x - 1, node->y)];
		if (left->entity == nullptr && !left->evaluated)
			addToSet(openSet, goal, node, left, _distanceStraight);

		Node* up = &_map[key(node->x, node->y - 1)];
		if (up->entity == nullptr && !up->evaluated)
			addToSet(openSet, goal, node, up, _distanceStraight);

		Node* dNode;
		if (right->entity == nullptr && down->entity == nullptr)
		{
			dNode = &_map[key(node->x + 1, node->y + 1)];
			if (dNode->entity == nullptr && !dNode->evaluated)
				addToSet(openSet, goal, node, dNode, _distanceDiagonal);
		}
		if (right->entity == nullptr && up->entity == nullptr)
		{
			dNode = &_map[key(node->x + 1, node->y - 1)];
			if (dNode->entity == nullptr && !dNode->evaluated)
				addToSet(openSet, goal, node, dNode, _distanceDiagonal);
		}
		if (left->entity == nullptr && down->entity == nullptr)
		{
			dNode = &_map[key(node->x - 1, node->y + 1)];
			if (dNode->entity == nullptr && !dNode->evaluated)
				addToSet(openSet, goal, node, dNode, _distanceDiagonal);
		}
		if (left->entity == nullptr && up->entity == nullptr)
		{
			dNode = &_map[key(node->x - 1, node->y - 1)];
			if (dNode->entity == nullptr && !dNode->evaluated)
				addToSet(openSet, goal, node, dNode, _distanceDiagonal);
		}
		/*
		Game::getInstance().getWorld()->draw(window);
		window->display();
		window->clear(sf::Color(216, 221, 206));
		*/
	}

	while (closedSet != nullptr)
	{
		closedSet->reset();
		closedSet = closedSet->next;
	}
	return result;
}

GridCoord WorldGrid::getWorldSize()
{
	return{ _worldSizeX - 1, _worldSizeY - 1 };
}

bool WorldGrid::insideMap(const int & x, const int & y)
{
	return (x > 0 && x < _worldSizeX - 1 && y > 0 && y < _worldSizeY - 1);
}

void WorldGrid::setEntity(const int& x, const int& y, Entity* entity)
{
	checkInsideMap(x, y);
	_map[key(x, y)].entity = entity;
	if (_entityPosition.find(entity) == _entityPosition.end())
	{
		_entityPosition.insert({ entity,{ { x, y } } });
	}
	else
	{
		_entityPosition.at(entity).push_back({ x, y });
	}
}

void WorldGrid::setEntity(const Vector2D& pos, Entity* entity)
{
	int x = pos.x / _gridSize;
	int y = pos.y / _gridSize;
	setEntity(x, y, entity);
}

void WorldGrid::removeEntity(const int& x, const int& y)
{
	checkInsideMap(x, y);
	GridCoord coord = { x, y };
	Utils::remove(_entityPosition.at(_map[key(x, y)].entity), coord);
	_map[key(x, y)].entity = nullptr;
}

void WorldGrid::removeEntity(Entity * entity)
{
	if (_entityPosition.find(entity) != _entityPosition.end())
	{
		for (const GridCoord& coord : _entityPosition.at(entity))
			_map[key(coord.x, coord.y)].entity = nullptr;

		_entityPosition.erase(entity);
	}
}

void WorldGrid::addToSet(Node*& openSet, Node* goal, Node* parent, Node* neighbor, const float& deltaDistance)
{
	/*	
	sf::RenderWindow* window = Game::getInstance().getWindow();
	sf::RectangleShape shape(sf::Vector2f(_gridSize, _gridSize));
	shape.setPosition(neighbor->x * _gridSize, neighbor->y * _gridSize);
	*/
	if (!neighbor->found)
	{
		neighbor->distanceTraveled = parent->distanceTraveled + deltaDistance;
		neighbor->distanceGoal = sqrt(pow(neighbor->x - goal->x, 2.0) + pow(neighbor->y - goal->y, 2.0));
		neighbor->distanceTotal = neighbor->distanceTraveled + neighbor->distanceGoal;
		neighbor->parent = parent;
		neighbor->found = true;
		openSet = neighbor->insertSort(openSet);
		//shape.setFillColor(sf::Color::Red);
		//window->draw(shape);
	}
	else if ((parent->distanceTraveled + deltaDistance + neighbor->distanceGoal) < neighbor->distanceTotal)
	{
		neighbor->distanceTraveled = parent->distanceTraveled + deltaDistance;
		neighbor->distanceTotal = neighbor->distanceTraveled + neighbor->distanceGoal;
		neighbor->parent = parent;
		openSet = neighbor->sort(openSet);
		//shape.setFillColor(sf::Color::Magenta);
		//window->draw(shape);
	}
}

void WorldGrid::checkInsideMap(const int & x, const int & y)
{
	if (x <= 0 || x >= _worldSizeX - 1 || y <= 0 || y >= _worldSizeY - 1)
		throw "Trying to access node outside Map";
}

void WorldGrid::debugDraw(Node * openSet, Node * closedSet, Node * goal, Node * current)
{
}

int WorldGrid::key(const int & x, const int & y)
{
	return x * _worldSizeY + y;
}
