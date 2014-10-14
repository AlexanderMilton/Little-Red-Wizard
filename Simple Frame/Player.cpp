#include "Player.h"
#include "InputHandler.h"
#include "ResourceManager.h"
#include "DebugOut.h"
#include "EntityManager.h"

const float walkSpeed = 1.8f;
const float jumpSpeed = -6.0f;
static const float gravity = 0.15f;
static const float terminalVelocity = 4.0f;
static const float reloadSpeed = 100.0f;
static const sf::Vector2f startingPosition = sf::Vector2f(50.0, 50.0);


Player::Player() :
	mIsJumping(true),
	mIsDoubleJumping(true),
	mFacingLeft(false),
	mPosition(startingPosition),
	
	// Error here, yo
	walkLeft	(std::make_shared<Animation>("left.png", 140, 2)),
	walkRight	(std::make_shared<Animation>("right.png", 140, 2)),
	idleLeft	(std::make_shared<Animation>("left_idle.png", 100, 1)),
	idleRight	(std::make_shared<Animation>("right_idle.png", 100, 1)),
	currentAnimation(idleRight),
	ground(0, 500, 720, 10)
{
	mReloadTimer.restart();
}

Player::~Player()
{
}

void Player::update(int input)
{
	// Casting spells
	if (input & InputHandler::Input::M_LEFT)
	{

		if (mReloadTimer.getElapsedTime().asMilliseconds() > reloadSpeed)
		{
			mIsReloading = false;
		}

		else
		{
			mIsReloading = true;
		}

		// We need a delay in the firing ability, 
		if (mIsReloading == false)
		{
			// Check facing direction to determine the spawn origin of the projectile
			if (mFacingLeft == true)
			{
				EntityManager::fireProjectile(sf::Vector2f(mPosition.x, mPosition.y - (getBoundingBox().height / 2)));
				mReloadTimer.restart();
			}

			if (mFacingLeft == false)
			{
				EntityManager::fireProjectile(sf::Vector2f(mPosition.x + (getBoundingBox().width), mPosition.y - (getBoundingBox().height / 2)));
				mReloadTimer.restart();
			}
		}
	}

	// Double Jumping
	if ((input & InputHandler::Input::SPACE) && (mIsJumping == true) && (mIsDoubleJumping == false) && (mVelocity.y < (-jumpSpeed / 1.2)))
	{
		mVelocity.y = jumpSpeed;
		mIsDoubleJumping = true;
	}

	// Jumping
	if ((input & InputHandler::Input::SPACE) && (mIsJumping == false) && (mIsDoubleJumping == false))
	{
		mVelocity.y = jumpSpeed;
		mIsJumping = true;
	}

	// Walk left
	if (input & InputHandler::Input::LEFT)
	{
		mVelocity.x = -walkSpeed;
		currentAnimation = walkLeft;
		mFacingLeft = true;
	}

	// Walk right
	else if (input & InputHandler::Input::RIGHT)
	{
		mVelocity.x = walkSpeed;
		currentAnimation = walkRight;
		mFacingLeft = false;
	}

	// Idle
	else
	{
		if (mVelocity.x > 0.1f){
			currentAnimation = idleRight;
		}

		if (mVelocity.x < -0.1f){
			currentAnimation = idleLeft;
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
	mPlayerBoundingBox = getBoundingBox();
	mPlayerBoundingBox.left = mPosition.x;
	mPlayerBoundingBox.top = mPosition.y;
	
	if (ground.intersects(mPlayerBoundingBox) && mVelocity.y > 0 && mPlayerBoundingBox.top + mPlayerBoundingBox.height / 2 < ground.top){
		mIsJumping = false;
		mIsDoubleJumping = false;
		mVelocity.y = 0;
		mPosition.y = ground.top - mPlayerBoundingBox.height;
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

void Player::draw(std::shared_ptr<sf::RenderWindow> window)
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

sf::FloatRect& Player::getBoundingBox()
{
	return currentAnimation->getSprite().getGlobalBounds();
}
