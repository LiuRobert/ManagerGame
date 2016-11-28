#pragma once
#include "Entity.h"
class ThinkingEntity :
	public Entity
{
public:
	virtual void think(const float& dt) = 0;

protected:
	ThinkingEntity() {};
	~ThinkingEntity() {};
};

