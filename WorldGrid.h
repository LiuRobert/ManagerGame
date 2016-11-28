#pragma once
#include "Parent.h"

#include "GridCoord.h"
#include <unordered_map>
#include <functional>
#include <queue>

struct Node;
class Entity;
class Vector2D;


class WorldGrid:
	public Parent
{
public:
	WorldGrid();
	~WorldGrid();
	void init(const int& worldWidth, const int& worldHeight, const float& gridSize);

	void addEntity(const int& x, const int& y, Entity* entity);
	Entity* getEntity(const int& x, const int& y);
	float getGridSize();
	std::vector<GridCoord> getPath(const GridCoord& from, const GridCoord& to);
	void setEntity(const int& x, const int& y, Entity* entity);
	void setEntity(const Vector2D& pos, Entity* entity);
	void removeEntity(const int& x, const int& y);
	void removeEntity(Entity* entity) override;

private:
	Entity* _pEdgeWall;
	int _worldSizeX;
	int _worldSizeY;
	float _gridSize;
	Node* _map;
	const float _distanceStraight;
	const float _distanceDiagonal;

	void addToSet(Node*& openSet, Node* goal, Node* parent, Node* neighbor, const float& deltaDistance);
	void debugDraw(Node* openSet, Node* closedSet, Node* goal, Node* current);
	int key(const int& x, const int& y);
};

