#include <SFML/Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>

#include "DebugOut.h"
#include "ResourceManager.h"
#include "SoundEngine.h"
#include "InputHandler.h"
#include "Player.h"

static const unsigned int WINDOW_WIDTH  = 512;
static const unsigned int WINDOW_HEIGHT = 512;


int main()
{
		// ----- INITIALIZE ----- //

		// Create a window
		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "<generic window name>");
		window.setFramerateLimit(144);
		window.setVerticalSyncEnabled(true);

		sf::Sprite backgroundImage(ResourceManager::getTexture("image.jpg"));
		sf::FloatRect imageSize = backgroundImage.getLocalBounds();
		int input = 0;
		InputHandler inputHandler;
		Player player;

    while (window.isOpen())
    {
        sf::Event event;
		while (window.pollEvent(event)){}

			// ----- MAIN LOOP ----- //

			// Check for termination, exit loop if true
			if (event.type == sf::Event::Closed || input == InputHandler::Input::ESCAPE)
			{
				window.close();
			}
                
			// Check for input
			input = inputHandler.update();

			// Update player
			player.update(input);



        window.clear();

		// Draw background
		window.draw(backgroundImage);

		// Draw player
		player.draw(&window);

        window.display();
    }

    return 0;
}