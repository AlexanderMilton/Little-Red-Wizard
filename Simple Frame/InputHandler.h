#ifndef _INPUT_MANAGER_
#define _INPUT_MANAGER_

class InputHandler
{
public:
	enum Input //Bit flags for input
	{
		NONE	= 0,
		LEFT	= 1 << 1,
		RIGHT	= 1 << 2,
		CONFIRM = 1 << 3,
		ESCAPE	= 1 << 4,
		SPACE	= 1 << 5,
		M_LEFT	= 1 << 6,
		M_RIGHT	= 1 << 7,
	};

	enum Mode
	{
		KEYBOARD,
		JOYSTICK
	};

	//returns bit flags in a char
	static int getGameInput();
	static void setInputMode(Mode mode);
	static Mode getInputMode();
	static float getStickDirection();
	static void setFocused(bool inFocus);
	static void setJoystickIndex(int index);
	static int getJoystickIndex();

private:
	InputHandler();
	static Mode inputMode;
	static int	joystickIndex;
	static bool isInFocus;
};

#endif // _INPUT_MANAGER_