#include "InputHandler.h"
#include "DebugOut.h"

#include "SFML\Window\Keyboard.hpp"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

// Check and handle keyboard input
int InputHandler::update()
{
	int input = Input::NONE;

	std::string dbgout;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		input += Input::LEFT;
		dbgout += "LEFT ";
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		input += Input::RIGHT;
		dbgout += "RIGHT ";
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		input += Input::CONFIRM;
		dbgout += "CONFIRM ";
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		input += Input::ESCAPE;
		dbgout += "ESCAPE ";
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		input += Input::SPACE;
		dbgout += "SPACE ";
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		input += Input::UP;
		dbgout += "UP ";
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		input += Input::DOWN;
		dbgout += "DOWN ";
	}


	dbgo::println(dbgout);
	
	return input;

}
