#include "WorkOrganizer.h"

#include "Game.h"
#include "Worker.h"
#include "World.h"
#include "Utils.h"


WorkOrganizer::WorkOrganizer()
{
}

WorkOrganizer::~WorkOrganizer()
{
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

void WorkOrganizer::control(const long & operation)
{

}
