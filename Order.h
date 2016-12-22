#pragma once
#include <vector>
#include "GridCoord.h"

class Order
{
public:
	enum Detail
	{
		Move,
		Work
	};

	struct Task
	{
		Detail what;
		GridCoord where;
	};
	
	Order() {}
	Order(std::vector<Task> tasks, int priority): tasks(tasks), priority(priority) {}
	~Order() {}

	bool operator<(const Order& rhs) const
	{
		return priority < rhs.priority;
	}

	std::vector<Task> tasks;
	int priority;
};

