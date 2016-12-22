#pragma once
#include "Controllable.h"

class KeyBinder:
	public Controllable
{
public:
	KeyBinder();
	~KeyBinder();

	void control(const long& operation) override;
	void init(const float& gridSize);

	enum Operations
	{
		SpawnWall,
		SpawnWorker,
		ShowCoords,
		RemoveEntity,
		MoveOrder
	};

private:
	float _gridSize;
};

