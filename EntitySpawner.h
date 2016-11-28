#pragma once
#include "Controllable.h"
#include "Vector2D.h"

class EntitySpawner:
	public Controllable
{
public:
	EntitySpawner();
	~EntitySpawner();
	void init(const float& gridSize);

	void control(const long& operation) override;
	static void spawnWall(const int& gridX, const int& gridY);
	static void spawnWorker(const int& gridX, const int& gridY);

private:
	float _gridSize;

	enum Operations
	{
		SpawnWall,
		SpawnWorker,
		ShowCoords
	};
};

