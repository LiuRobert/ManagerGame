#include "KeyboardController.h"

#include "Controllable.h"
#include "Utils.h"


KeyboardController::KeyboardController()
{
}


KeyboardController::~KeyboardController()
{
}

void KeyboardController::addKeyBind(const std::vector<KeyActivater>& keyActivaters, const long& operation, Controllable* controllable)
{
	Keybind keybind{ keyActivaters, operation, controllable };
	_keybinds.push_back(keybind);
	controllable->addController(this);
}

void KeyboardController::removeControllabe(Controllable* controllable)
{
	// TODO
	/*
	auto it = _keybinds.begin();
	while (it != _keybinds.end())
	{
	if (it->controllable == controllable)
	it = _keybinds.erase(it);
	else
	it++;
	}
	*/
}

void KeyboardController::think()
{
	std::vector<sf::Keyboard::Key> currentKeysPressed;;
	for (size_t i = 0, size = _keybinds.size(); i < size; i++)
	{
		if (_keybinds[i].controllable->activate())
		{
			bool activate = true;
			for (size_t j = 0, size = _keybinds[i].keyActivaters.size(); j < size; j++)
			{
				bool pressed = false;
				if (sf::Keyboard::isKeyPressed(_keybinds[i].keyActivaters[j].key))
				{
					pressed = true;
					Utils::addUnique(currentKeysPressed, _keybinds[i].keyActivaters[j].key);
				}
				switch (_keybinds[i].keyActivaters[j].keyState)
				{
				case KeyState::keyPressed:
					if (!pressed)
					{
						activate = false;
					}
					break;
				case KeyState::onKeyDown:
					if (!pressed || keysPressedLast(_keybinds[i].keyActivaters[j].key))
					{
						activate = false;
					}
					break;
				case KeyState::onKeyUp:
					if (pressed || !keysPressedLast(_keybinds[i].keyActivaters[j].key))
					{
						activate = false;
					}
					break;
				}

			}
			if (activate)
			{
				_keybinds[i].controllable->control(_keybinds[i].operation);
			}
		}
	}
	_lastKeysPressed = currentKeysPressed;
}

bool KeyboardController::keysPressedLast(const sf::Keyboard::Key& key)
{
	return Utils::contains(_lastKeysPressed, key);
}