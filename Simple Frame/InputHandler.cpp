#include "InputHandler.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Joystick.hpp>

#include "DebugOut.h"

static const float JOYSTICK_DEADZONE = 20.0f;
InputHandler::Mode InputHandler::inputMode;
int InputHandler::joystickIndex = 0;
bool InputHandler::isInFocus = true;

static enum XboxControllerButtons
{
	A,
	B,
	X,
	Y,
	LEFT_BUTTON,
	RIGHT_BUTTON,
	BACK,
	START,
	LEFT_STICK,
	RIGHT_STICK,
};

int getKeyboardInput()
{
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
		input += InputHandler::Input::SPACE;
		dbgout += "SPACE ";
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		input += InputHandler::Input::M_LEFT;
		dbgout += "UP ";
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		input += InputHandler::Input::M_RIGHT;
		dbgout += "DOWN ";
	}


	dbgo::println(dbgout);

	return input;
}

int getJoystickInput()
{
	int input = InputHandler::Input::NONE;

	std::string dbgout;
	if (sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::X) < -JOYSTICK_DEADZONE ||
		sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::PovY) < -JOYSTICK_DEADZONE)
	{
		input += InputHandler::Input::LEFT;
		dbgout += "LEFT ";
	}

	if (sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::X) > JOYSTICK_DEADZONE ||
		sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::PovY) > JOYSTICK_DEADZONE)
	{
		input += InputHandler::Input::RIGHT;
		dbgout += "RIGHT ";
	}

	if (sf::Joystick::isButtonPressed(InputHandler::getJoystickIndex(), XboxControllerButtons::A))
	{
		input += InputHandler::Input::CONFIRM;
		dbgout += "CONFIRM ";
	}

	if (sf::Joystick::isButtonPressed(InputHandler::getJoystickIndex(), XboxControllerButtons::START))
	{
		input += InputHandler::Input::ESCAPE;
		dbgout += "ESCAPE ";
	}

	if (sf::Joystick::isButtonPressed(InputHandler::getJoystickIndex(), XboxControllerButtons::B))
	{
		input += InputHandler::Input::SPACE;
		dbgout += "SPACE ";
	}

	if (sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::Y) < -JOYSTICK_DEADZONE ||
		sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::PovX) > JOYSTICK_DEADZONE)
	{
		input += InputHandler::Input::M_LEFT;
		dbgout += "UP ";
	}

	if (sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::Y) > JOYSTICK_DEADZONE ||
		sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::PovX) < -JOYSTICK_DEADZONE)
	{
		input += InputHandler::Input::M_RIGHT;
		dbgout += "DOWN ";
	}


	dbgo::println(dbgout);

	return input;
}

int InputHandler::getGameInput()
{
	if (!isInFocus)
	{
		return Input::NONE;
	}
	switch (inputMode)
	{
	case InputHandler::Mode::KEYBOARD:
		return getKeyboardInput();
		break;
	case InputHandler::Mode::JOYSTICK:
		return getJoystickInput();
		break;
	}
	dbgo::println("InputHandler.cpp: Invalid InputMode");
	return Input::NONE;
}

void InputHandler::setInputMode(InputHandler::Mode mode)
{
	inputMode = mode;
}

InputHandler::Mode InputHandler::getInputMode()
{
	return inputMode;
}

float InputHandler::getStickDirection()
{
	return (sf::Joystick::getAxisPosition(InputHandler::getJoystickIndex(), sf::Joystick::Axis::X) / 100.0f);
}

void InputHandler::setFocused(bool inFocus)
{
	isInFocus = inFocus;
}

void InputHandler::setJoystickIndex(int index)
{
	joystickIndex = index;
}

int InputHandler::getJoystickIndex()
{
	return joystickIndex;
}