#pragma once
#include <SFML\Window\Event.hpp>

class Controllable;

class Controller
{
public:
	Controller();
	~Controller();

	virtual void removeControllabe(Controllable* controllable) = 0;
};

