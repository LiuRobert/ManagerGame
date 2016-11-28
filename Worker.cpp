#include "Worker.h"
#include <math.h>
#include "Game.h"
#include "World.h"
#include "WorldGrid.h"

#include "Node.h"


Worker::Worker(const float& x, const float& y)
{
	_shape.setRadius(8);
	_shape.setFillColor(sf::Color::Green);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(2.0f);
	setPosition(x, y);
	_drawables.push_back(&_shape);
	_gridSize = Game::getInstance().getWorld()->getWorldGrid()->getGridSize();
}

Worker::Worker(const GridCoord& coords)
{
	_gridSize = Game::getInstance().getWorld()->getWorldGrid()->getGridSize();
	_shape.setRadius(8);
	_shape.setFillColor(sf::Color::Green);
	_shape.setOutlineColor(sf::Color::Black);
	_shape.setOutlineThickness(2.0f);
	setPosition(coords.x * _gridSize + 4, coords.y * _gridSize + 4);
	_drawables.push_back(&_shape);
	_goal = { 1, 1 };
}

Worker::~Worker()
{
}

void Worker::control(const long & operation)
{

}

void Worker::think(const float& dt)
{
	WorldGrid* worldgrid = Game::getInstance().getWorld()->getWorldGrid();
	if (_path.empty())
	{
		_path = worldgrid->getPath(mapPosition(), _goal);
	}


}

void Worker::setPosition(const Vector2D& pos)
{
	_pos = pos;
	_shape.setPosition(pos.sfmlVector());
}

void Worker::setPosition(const float& x, const float& y)
{
	_pos.x = x;
	_pos.y = y;
	_shape.setPosition(x, y);
}

GridCoord Worker::mapPosition()
{
	return GridCoord(_pos.x / _gridSize, _pos.y / _gridSize);
}
