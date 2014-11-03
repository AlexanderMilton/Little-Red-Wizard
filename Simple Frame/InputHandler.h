#ifndef _INPUT_HANDLER_
#define _INPUT_HANDLER_

#include <string>

class InputHandler

{
public:
	InputHandler();
	~InputHandler();

	int& update();
	int updateGlobal(int input);
	int updatePlayer(int input);
	bool isSpacePressed;

	enum Input
	{
		NONE		= 0,
		LEFT		= 1 << 1,
		RIGHT		= 1 << 2,
		CONFIRM		= 1 << 3,
		ESCAPE		= 1 << 4,
		SPACE		= 1 << 5,
		UP			= 1 << 6,
		DOWN		= 1 << 7,
		M_LEFT		= 1 << 8,
		M_RIGHT		= 1 << 9,
	};
};

#endif	// _INPUT_HANDLER_