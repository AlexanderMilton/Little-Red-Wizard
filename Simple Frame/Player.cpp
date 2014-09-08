#include "Player.h"
#include "InputHandler.h"
#include "ResourceManager.h"


const float walkSpeed = 1.5;
const float jumpSpeed = -6;
static const float gravity = 0.2;
static const float terminalVelocity = 3;
static const sf::Vector2f startingPosition = sf::Vector2f(50.0, 50.0);


Player::Player() :
	isJumping(true),
	mPosition(startingPosition),
	walkLeft("left.png", 100, 3),
	walkRight("right.png", 100, 3),
	idleLeft("left_idle.png", 100, 1),
	idleRight("right_idle.png", 100, 1),
	currentAnimation(&idleRight),
	ground(0, 400, 720, 10)
{
}

Player::~Player()
{
}

void Player::update(int input)
{


	// Jumping
	if ((input & InputHandler::Input::SPACE) && (isJumping == false))
	{
		mVelocity.y = jumpSpeed;
		isJumping = true;
	}


	// Walk left
	if (input & InputHandler::Input::LEFT)
	{
		mVelocity.x = -walkSpeed;
		currentAnimation = &walkLeft;
	}

	// Walk right
	else if (input & InputHandler::Input::RIGHT)
	{
		mVelocity.x = walkSpeed;
		currentAnimation = &walkRight;
	}

	// Idle
	else
	{
		if (mVelocity.x > 0.1f){
			currentAnimation = &idleRight;
		}

		if (mVelocity.x < -0.1f){
			currentAnimation = &idleLeft;
		}

		mVelocity.x = 0;
	}



	// Gravity & Terminal velocity
	mVelocity.y += gravity;

	if (mVelocity.y > terminalVelocity){
		mVelocity.y = terminalVelocity;
	}

	mPosition += mVelocity;

	

	// Ground and Wall collision
	playerBoundingBox = getBoundingBox();
	playerBoundingBox.left = mPosition.x;
	playerBoundingBox.top = mPosition.y;
	
	if (ground.intersects(playerBoundingBox) && mVelocity.y > 0 && playerBoundingBox.top + playerBoundingBox.height / 2 < ground.top){
		isJumping = false;
		mVelocity.y = 0;
		mPosition.y = ground.top - playerBoundingBox.height;
	}



	// In case player would glitch out of the area
	if (mPosition.y > 450)
	{
		mPosition = startingPosition;
	}



	// Update animation
	currentAnimation->update();
	currentAnimation->setPosition(mPosition);
}

void Player::draw(sf::RenderWindow * window)
{
	window->draw(getSprite());
}

const sf::Sprite& Player::getSprite() const
{
	return currentAnimation->getSprite();
}

const sf::Vector2f& Player::getPosition() const
{
	return mPosition;
}

sf::FloatRect Player::getBoundingBox()
{
	sf::Sprite sprite = currentAnimation->getSprite();
	return sprite.getGlobalBounds();
}
