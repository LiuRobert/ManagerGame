#pragma once
#include "ThinkingEntity.h"
#include "Controllable.h"
#include "GridCoord.h"
#include "Order.h"

class Worker :
	public ThinkingEntity
{
public:
	Worker(const float& x, const float& y);
	Worker(const GridCoord& coords);
	~Worker();

	bool haveOrder();
	void think(const float& dt) override;
	void setOrder(const Order& order);
	void setPosition(const Vector2D& pos) override;
	void setPosition(const float& x, const float& y) override;


private:
	sf::CircleShape _shape;
	float _gridSize;
	GridCoord _goal;
	bool _hasGoal;
	bool _haveOrder;
	float _movementSpeed;
	GridCoord _next;
	std::vector<GridCoord> _path;
	Vector2D _nextPos;
	Order _order;
	Order::Task _task;

	GridCoord mapPosition();
};

