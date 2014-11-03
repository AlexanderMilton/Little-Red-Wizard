#ifndef _PLAYER_
#define _PLAYER_

#include <memory>

#include "Animation.h"
#include "Projectile.h"
#include "EntityManager.h"

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\System\Vector2.hpp"

class Player
{
public:
	Player();
	~Player();

	void update(int& input, EntityManager& entityManager);
	void draw(std::shared_ptr <sf::RenderWindow> window);
	
	void handleSpells(int& input, EntityManager& entityManager);
	void handleWalk(int& input);
	void handleJump(int& input);
	
	const sf::Sprite& getSprite() const;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect& getBoundingBox();

private:
	std::shared_ptr <Animation>  walkLeft;
	std::shared_ptr <Animation>  idleLeft;
	std::shared_ptr <Animation>  walkRight;
	std::shared_ptr <Animation>  idleRight;
	std::shared_ptr <Animation> currentAnimation;
	
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