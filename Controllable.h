#pragma once
#include <vector>
#include "Utils.h"

class Controller;

class Controllable
{
public:
	virtual ~Controllable();

	virtual bool activate();
	void addController(Controller* controller);
	virtual void control(const long& operation) = 0;

protected:
	Controllable();

private:
	std::vector<Controller*> _controllers;
};

