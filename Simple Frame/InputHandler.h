#ifndef _INPUT_HANDLER_
#define _INPUT_HANDLER_

#include <string>

#include <SFML\Window\Event.hpp>

class InputHandler

{
public:
	InputHandler();
	~InputHandler();
	int& update();

	enum Input
	{
		NONE = 0,
		LEFT = 1 << 1,
		RIGHT = 1 << 2,
		CONFIRM = 1 << 3,
		ESCAPE = 1 << 4,
		SPACE = 1 << 5,
		UP = 1 << 6,
		DOWN = 1 << 7,
		M_LEFT = 1 << 8,
		M_RIGHT = 1 << 9,
	};

private:
	sf::Event event;

};

#endif	// _INPUT_HANDLER_