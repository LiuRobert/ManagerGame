#pragma once
#include "Controllable.h"
#include "Parent.h"

class Worker;

class WorkOrganizer:
	public Parent,
	public Controllable
{
public:
	WorkOrganizer();
	~WorkOrganizer();

	void control(const long& operation) override;
	void addWorker(Worker* worker);
	void removeEntity(Entity* entity) override;

private:
	std::vector<Worker*> _workers;
};

