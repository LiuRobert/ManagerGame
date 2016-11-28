#include "Entity.h"
#include "Parent.h"
#include "Utils.h"


Entity::Entity()
{
}


Entity::~Entity()
{
	for (const auto& p : _parents)
	{
		p->removeEntity(this);
	}
}

void Entity::addParent(Parent* parent)
{
	Utils::addUnique(_parents, parent);
}

Vector2D Entity::getPosition()
{
	return _pos;
}

void Entity::setPosition(const Vector2D& pos)
{
	_pos = pos;
}

void Entity::setPosition(const float& x, const float& y)
{
	_pos.x = x;
	_pos.y = y;
}

void Entity::draw(sf::RenderWindow * window)
{
	for (size_t i = 0, size = _drawables.size(); i < size; i++)
	{
		window->draw(*_drawables[i]);
	}
}
