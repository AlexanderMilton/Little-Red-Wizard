#ifndef _GAME_ENGINE_
#define _GAME_ENGINE_

#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>

#include "DebugOut.h"
#include "ResourceManager.h"
#include "EntityManager.h"
#include "SoundEngine.h"
#include "InputHandler.h"
#include "Player.h"

#include <memory>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	int run();

private:
	std::shared_ptr <sf::RenderWindow> window;
	sf::FloatRect imageSize;
	sf::Sprite mBackgroundImage;
	int input;
	InputHandler mInputHandler;
	Player mPlayer;
};

#endif	// _GAME_ENGINE_