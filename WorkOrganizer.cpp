#include "WorkOrganizer.h"

#include "Game.h"
#include "Order.h"
#include "Worker.h"
#include "World.h"
#include "Utils.h"


WorkOrganizer::WorkOrganizer()
{
}

WorkOrganizer::~WorkOrganizer()
{
}

void WorkOrganizer::addOrder(const Order& order)
{
	_orders.push(order);
}

void WorkOrganizer::addWorker(Worker* worker)
{
	World* world = Game::getInstance().getWorld();
	_workers.push_back(worker);
	worker->addParent(this);
}

void WorkOrganizer::removeEntity(Entity* entity)
{
	Utils::remove(_workers, entity);
}

void WorkOrganizer::think()
{
	if (!_orders.empty())
	{
		for (const auto& w : _workers)
		{
			if (!w->haveOrder())
			{
				w->setOrder(_orders.top());
				_orders.pop();
				if (_orders.empty())
					break;
			}
		}
	}
}
