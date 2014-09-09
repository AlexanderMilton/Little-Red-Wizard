#include "InputHandler.h"
#include "DebugOut.h"

#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Event.hpp"


InputHandler::InputHandler() :
	isSpacePressed(false)
{
}


InputHandler::~InputHandler()
{
}

// Check and handle keyboard input
int InputHandler::update()
{
	// Reset input
	int input = InputHandler::Input::NONE;

	std::string dbgout;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		input += InputHandler::Input::LEFT;
		dbgout += "LEFT ";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		input += InputHandler::Input::RIGHT;
		dbgout += "RIGHT ";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		input += InputHandler::Input::CONFIRM;
		dbgout += "CONFIRM ";
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		input += InputHandler::Input::ESCAPE;
		dbgout += "ESCAPE ";
	}


	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (isSpacePressed == false)
			{
				input += InputHandler::Input::SPACE;
				isSpacePressed = true;
			}
		}

		else
		{
			isSpacePressed = false;
		}

		dbgout += "SPACE ";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		input += InputHandler::Input::UP;
		dbgout += "UP ";
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		input += InputHandler::Input::DOWN;
		dbgout += "DOWN ";
	}


	dbgo::println(dbgout);
	
	return input;

}
