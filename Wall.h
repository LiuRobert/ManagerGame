#pragma once
#include "Entity.h"

class Wall :
	public Entity
{
public:
	Wall(const float& x, const float& y);
	~Wall();

	void setPosition(const float& x, const float& y) override;

private:
	sf::RectangleShape _shape;
};

