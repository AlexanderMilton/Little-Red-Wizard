#include "Player.h"
#include "InputHandler.h"
#include "ResourceManager.h"
#include "DebugOut.h"

const float walkSpeed= 9.9f;					// In 10 "Meters" per second
const float jumpSpeed = -1.2f;					// In 10 "Meters" per second
static const float gravity = 0.98f;				// In 10 "Meters" per second per second
static const float terminalVelocity = 5.55f;	// In 10 "Meters" per second
static const float reloadTime = 100.0f;			// Milliseconds
static const float jumpRechargeTime = 10.0f;	// Milliseconds
static const sf::Vector2f startingPosition = sf::Vector2f(50.0, 50.0);


Player::Player() :
	mIsJumping(true),
	mIsDoubleJumping(true),
	mFacingLeft(false),
	mPosition(startingPosition),
	
	walkLeft	(std::make_shared<Animation>("left.png", 140, 2)),
	walkRight	(std::make_shared<Animation>("right.png", 140, 2)),
	idleLeft	(std::make_shared<Animation>("left_idle.png", 100, 1)),
	idleRight	(std::make_shared<Animation>("right_idle.png", 100, 1)),
	currentAnimation(idleRight),
	ground(0, 500, 720, 10)
{
	mReloadTimer.restart();
	mJumpTimer.restart();
}

Player::~Player()
{
}

void Player::update(int& input, EntityManager& entityManager)
{
	
	handleSpells(input, entityManager);

	handleJump(input);

	handleWalk(input);


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

void Player::handleSpells(int& input, EntityManager& entityManager)
{
	// Casting spells
	if (input & InputHandler::Input::M_LEFT)
	{

		if (mReloadTimer.getElapsedTime().asMilliseconds() > reloadTime)
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
				entityManager.fireProjectile(sf::Vector2f(mPosition.x, mPosition.y - (getBoundingBox().height / 2)));
				mReloadTimer.restart();
			}
			if (mFacingLeft == false)
			{
				entityManager.fireProjectile(sf::Vector2f(mPosition.x + (getBoundingBox().width), mPosition.y - (getBoundingBox().height / 2)));
				mReloadTimer.restart();
			}
		}
	}
}

void Player::handleJump(int& input)
{
	if (input & InputHandler::Input::SPACE)
	{
		if (!mIsJumping)
		{
			mVelocity.y = jumpSpeed;
			mIsJumping = true;
		}

		else if (mIsJumping && !mIsDoubleJumping && mJumpTimer.getElapsedTime().asMilliseconds() > jumpRechargeTime)
		{
			mVelocity.y = jumpSpeed;
			mIsDoubleJumping = true;
		}
	}


	/*
	if (!mIsJumping)
	{
	mVelocity.y = -jumpSpeed;
	mIsJumping = true;
	}

	else if (mIsJumping && mJumpTimer.getElapsedTime().asMilliseconds() > jumpRechargeTime)
	{
	mVelocity.y = -jumpSpeed;
	mIsDoubleJumping = true;
	}*/


	/*

	// Double Jumping
	if ((input & InputHandler::Input::SPACE) && (mIsJumping == true) && (mIsDoubleJumping == false) && (mJumpTimer.getElapsedTime().asMilliseconds() > jumpRechargeTime))
	{
		mVelocity.y = jumpSpeed;
		mIsDoubleJumping = true;
	}

	// Jumping
	if ((input & InputHandler::Input::SPACE) && (mIsJumping == false) && (mIsDoubleJumping == false))
	{
		mVelocity.y = jumpSpeed;
		mIsJumping = true;
		mJumpTimer.restart();
	}

	*/

}

void Player::handleWalk(int& input)
{
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
