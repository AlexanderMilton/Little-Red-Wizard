#include "GameEngine.h"

static const unsigned int WINDOW_WIDTH = 512;
static const unsigned int WINDOW_HEIGHT = 512;


GameEngine::GameEngine() :
	mBackgroundImage(ResourceManager::getTexture("image.jpg")),
	imageSize(mBackgroundImage.getLocalBounds()),
	input(0),
	mPlayer()
{
	// ----- INITIALIZE ----- //

	// Create a window
	//sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "<generic window name>");
	window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "<generic window name>"));
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(true);
}


GameEngine::~GameEngine()
{
}

int GameEngine::run()
{
	
		// ---------- MAIN LOOP ---------- //



	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event)){}


		// ----- UPDATE ----- //

		// Check for termination, exit loop if true
		if (event.type == sf::Event::Closed || input == InputHandler::Input::ESCAPE)
		{
			window->close();
		}

		// Check for input
		input = mInputHandler.update();

		// Update player
		mPlayer.update(input);



		// ----- RENDER ----- //

		// Clear window
		window->clear();

		// Draw background
		window->draw(mBackgroundImage);

		// Draw player
		mPlayer.draw(window);

		// Display window
		window->display();
	}

	return 0;
}