#ifndef _INPUT_HANDLER_
#define _INPUT_HANDLER_

#include <string>


enum Input
	{
		NONE    = 0,
		LEFT    = 1 << 1,
		RIGHT   = 1 << 2,
		CONFIRM = 1 << 3,
		ESCAPE  = 1 << 4,
		SPACE   = 1 << 5,
		UP      = 1 << 6,
		DOWN    = 1 << 7,
};

class InputHandler

{
public:
	InputHandler();
	~InputHandler();

	int update();
	int updateGlobal(int input);
	int updatePlayer(int input);

};

#endif	// _INPUT_HANDLER_