#pragma once
#include "Vector2D.h"
#include <SFML\Graphics.hpp>

class Parent;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void addParent(Parent* parent);
	virtual Vector2D getPosition();
	virtual void setPosition(const Vector2D& pos);
	virtual void setPosition(const float& x, const float& y);
	virtual void draw(sf::RenderWindow* window);

protected:
	std::vector<sf::Drawable*> _drawables;
	Vector2D _pos;

private:
	std::vector<Parent*> _parents;
};

