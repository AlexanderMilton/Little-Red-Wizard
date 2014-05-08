#include <SFML/Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>

#include "DebugOut.h"
#include "ResourceManager.h"
#include "SoundEngine.h"
#include "Player.h"

static const int WINDOW_WIDTH  = 720;
static const int WINDOW_HEIGHT = 405;




	enum Input		// Bit flags for input
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

// Check and handle keyboard input
int handleInput()
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


int main()
{
		// ----- INITIALIZE ----- //

		sf::Sprite image(ResourceManager::getTexture("image.jpg"));
		sf::FloatRect imageSize = image.getLocalBounds();
		int input = 0;
		Player player;

		// Open a window
		sf::RenderWindow window(sf::VideoMode(imageSize.width, imageSize.height), "<generic window name>");
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

			// ----- MAIN LOOP ----- //

			if (event.type == sf::Event::Closed || input == Input::ESCAPE)
                window.close();

			input = handleInput();

			player.update(input);



        }

        window.clear();
        window.draw(image);
        window.display();
    }

    return 0;
}
