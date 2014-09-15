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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (isSpacePressed == false)
		{
			input += InputHandler::Input::SPACE;
			isSpacePressed = true;
		}
		dbgout += "SPACE ";
	}

	else
	{
		isSpacePressed = false;
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		input += InputHandler::Input::M_LEFT;
		dbgout += "M_LEFT ";
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		input += InputHandler::Input::M_RIGHT;
		dbgout += "M_RIGHT ";
	}


	dbgo::println(dbgout);
	
	return input;

}
