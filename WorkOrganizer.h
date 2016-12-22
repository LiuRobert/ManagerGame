#pragma once
#include <queue>
#include "Parent.h"

class Worker;
class Order;

class WorkOrganizer:
	public Parent
{
public:
	WorkOrganizer();
	~WorkOrganizer();

	void addOrder(const Order& order);
	void addWorker(Worker* worker);
	void removeEntity(Entity* entity) override;
	void think();


private:
	std::priority_queue<Order> _orders;
	std::vector<Worker*> _workers;
};

