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
	void receiveInput();
	int run();

private:
	std::shared_ptr <sf::RenderWindow> window;
	sf::FloatRect imageSize;
	sf::Sprite mBackgroundImage;
	sf::Event mEvent;
	bool inFocus;
	int input;
	//InputHandler mInputHandler;
	EntityManager mEntityManager;
	Player mPlayer;

	sf::View view;	// Fulkod
};

#endif	// _GAME_ENGINE_