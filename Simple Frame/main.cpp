#include <SFML/Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>

#include "DebugOut.h"
#include "ResourceManager.h"
#include "SoundEngine.h"
#include "InputHandler.h"
#include "Player.h"

static const unsigned int WINDOW_WIDTH  = 1420;
static const unsigned int WINDOW_HEIGHT = 805;






int main()
{
		// ----- INITIALIZE ----- //

		sf::Sprite image(ResourceManager::getTexture("image.jpg"));
		sf::FloatRect imageSize = image.getLocalBounds();
		int input = 0;
		InputHandler inputHandler;
		Player player;

		// Create a window
		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "<generic window name>");
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

			// ----- MAIN LOOP ----- //

			// Check for termination, exit loop if true
			if (event.type == sf::Event::Closed || input == Input::ESCAPE)
                window.close();

			// Check for input
			input = inputHandler.update();

			// Update player
			player.update(input);


        }

        window.clear();

		// Draw player
		player.draw(&window);

        window.display();
    }

    return 0;
}
