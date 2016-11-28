#pragma once

class Entity;

class Parent
{
public:
	virtual void removeEntity(Entity* entity) = 0;

protected:
	Parent() {}
	virtual ~Parent(){}
};

