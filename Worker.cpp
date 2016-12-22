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
	_hasGoal = false;
	_haveOrder = false;
	_movementSpeed = 2;
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
	_hasGoal = false;
	_haveOrder = false;
	_movementSpeed = 2;
}

Worker::~Worker()
{
}

bool Worker::haveOrder()
{
	return _haveOrder;
}

void Worker::think(const float& dt)
{
	WorldGrid* worldgrid = Game::getInstance().getWorld()->getWorldGrid();
	if (!_hasGoal && _haveOrder)
	{
		_task = _order.tasks.back();
		_order.tasks.pop_back();
		_hasGoal = true;
	}

	if (_hasGoal)
	{
		if(_path.empty())
			_path = worldgrid->getPath(mapPosition(), _task.where);
		
		Vector2D deltaGoal(_path.back().x * _gridSize, _path.back().y * _gridSize);
		Vector2D direction = (deltaGoal - _pos).getNormalized();
 		direction = _pos + direction * _movementSpeed ;
		setPosition(direction);
		
		if ((_pos - deltaGoal).length() < 5)
			_path.pop_back();

		if (_path.empty())
		{
			_hasGoal = false;
			if (_order.tasks.empty())
				_haveOrder = false;
		}
	}
}

void Worker::setOrder(const Order& order)
{
	_order = order;
	_haveOrder = true;
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
