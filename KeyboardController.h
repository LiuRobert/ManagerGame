#pragma once
#include "Controller.h"
#include <vector>

class KeyboardController :
	public Controller
{
public:
	KeyboardController();
	~KeyboardController();

	enum KeyState
	{
		onKeyDown,
		onKeyUp,
		keyPressed
	};

	struct KeyActivater
	{
		const sf::Keyboard::Key key;
		const KeyState keyState;
	};

	void addKeyBind(const std::vector<KeyActivater>& keyActivaters, const long& operation, Controllable* controllable);
	void removeControllabe(Controllable* controllable) override;
	void think();

private:
	struct Keybind
	{
		const std::vector<KeyActivater> keyActivaters;
		const long operation;
		Controllable* controllable;
	};

	std::vector<Keybind> _keybinds;
	std::vector<sf::Keyboard::Key> _lastKeysPressed;

	bool keysPressedLast(const sf::Keyboard::Key& key);
};

