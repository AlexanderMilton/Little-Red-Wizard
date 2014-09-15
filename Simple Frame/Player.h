#ifndef _PLAYER_
#define _PLAYER_

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\System\Vector2.hpp"

#include "Animation.h"
#include "Projectile.h"

#include <memory>

class Player
{
public:
	Player();
	~Player();

	void update(int input);
	void draw(std::shared_ptr <sf::RenderWindow> window);
	const sf::Sprite& getSprite() const;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getBoundingBox();

private:
	std::unique_ptr <Animation>  walkLeft;
	std::unique_ptr <Animation>  idleLeft;
	std::unique_ptr <Animation>  walkRight;
	std::unique_ptr <Animation>  idleRight;
	std::unique_ptr <Animation> currentAnimation;
	
	sf::FloatRect mPlayerBoundingBox;
	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	bool mIsJumping;
	bool mIsDoubleJumping;
	bool mFacingLeft;
	bool mIsReloading;
	sf::Clock mReloadTimer;

	sf::FloatRect ground;	// To be replaced by a world class
};

#endif	// _PLAYER_