#include "GameEngine.h"

static const unsigned int WINDOW_WIDTH = 512;
static const unsigned int WINDOW_HEIGHT = 512;


GameEngine::GameEngine() :
	//mBackgroundImage(ResourceManager::getTexture("image.jpg")),
	imageSize(mBackgroundImage.getLocalBounds()),
	input(0),
	mPlayer()
{
	// ----- INITIALIZE ----- //

	// Create a window
	//sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "<generic window name>");
	window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "<generic window name>"));
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
}


GameEngine::~GameEngine()
{
}

int GameEngine::run()
{
	
	// -------------------- MAIN LOOP -------------------- //

	while (window->isOpen())
	{

		while (window->isOpen())
		{
			window->pollEvent(mEvent);

			switch (mEvent.type)
			{
			case sf::Event::KeyPressed:
				input = InputHandler::getGameInput();		// Check for input
				break;
			case sf::Event::JoystickButtonPressed:
				InputHandler::setInputMode(InputHandler::Mode::JOYSTICK);
				InputHandler::setJoystickIndex(mEvent.joystickButton.joystickId);
				break;
			case sf::Event::JoystickMoved:
				InputHandler::setInputMode(InputHandler::Mode::JOYSTICK);
				InputHandler::setJoystickIndex(mEvent.joystickMove.joystickId);
				break;
			case sf::Event::Resized:
				window->setView(sf::View(sf::FloatRect(0, 0, float (mEvent.size.width), float (mEvent.size.height))));
				view = window->getView();
				window->setView(view);
				break;
			case sf::Event::LostFocus:
				 inFocus = false;
				break;
			case sf::Event::GainedFocus:
				inFocus = true;
				break;
			case sf::Event::Closed:
			case InputHandler::Input::ESCAPE:
				window->close();
				return 0;
			}


			// ---------- UPDATE ---------- //

			// Update player
			mPlayer.update(input, mEntityManager);

			// ---------- RENDER ---------- //

			// Clear window
			window->clear();

			// Draw background
			window->draw(mBackgroundImage);

			// Draw player
			mPlayer.draw(window);

			// Display window
			window->display();
		}
	}

	return 0;
}