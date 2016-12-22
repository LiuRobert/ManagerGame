#pragma once
#include "Vector2D.h"

class EntitySpawner
{
public:
	EntitySpawner();
	~EntitySpawner();

	static void spawnWall(const int& gridX, const int& gridY);
	static void spawnWorker(const int& gridX, const int& gridY);
	static void removeEntity(const int& gridX, const int& gridY);
};

