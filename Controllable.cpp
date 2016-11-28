#include "Controllable.h"
#include "Controller.h"


Controllable::Controllable()
{
}


Controllable::~Controllable()
{
	for (const auto& c : _controllers)
	{
		c->removeControllabe(this);
	}
}

bool Controllable::activate()
{
	return true;
}

void Controllable::addController(Controller* controller)
{
	Utils::addUnique(_controllers, controller);
}
