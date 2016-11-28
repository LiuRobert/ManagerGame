#include "Wall.h"



Wall::Wall(const float& x, const float& y)
{
	_shape.setSize(sf::Vector2f(23.0f, 23.0f));
	_shape.setFillColor(sf::Color(244, 158, 66));
	_shape.setOutlineThickness(1.0f);
	_shape.setOutlineColor(sf::Color::Black);
	setPosition(x, y);
	_drawables.push_back(&_shape);
}


Wall::~Wall()
{
}

void Wall::setPosition(const float & x, const float & y)
{
	_pos.x = x;
	_pos.y = y;
	_shape.setPosition(x, y);
}
