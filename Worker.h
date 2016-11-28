#pragma once
#include "ThinkingEntity.h"
#include "Controllable.h"
#include "GridCoord.h"


class Worker :
	public ThinkingEntity,
	public Controllable
{
public:
	Worker(const float& x, const float& y);
	Worker(const GridCoord& coords);
	~Worker();

	void control(const long& operation) override;
	void think(const float& dt) override;
	void setPosition(const Vector2D& pos) override;
	void setPosition(const float& x, const float& y) override;

private:
	sf::CircleShape _shape;
	float _gridSize;
	GridCoord _goal;
	GridCoord _next;
	std::vector<GridCoord> _path;
	Vector2D _nextPos;

	GridCoord mapPosition();
};

