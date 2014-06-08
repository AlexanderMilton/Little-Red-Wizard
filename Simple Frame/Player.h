#ifndef _PLAYER_
#define _PLAYER_

#include "Animation.h"
#include "SFML\Graphics\RenderWindow.hpp"

class Player
{
public:
	Player();
	~Player();

	void update(int input);
	void draw(sf::RenderWindow* window);
	const sf::Sprite& getSprite() const;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getBoundingBox();

private:
	Animation walkLeft;
	Animation idleLeft;
	Animation walkRight;
	Animation idleRight;
	Animation* currentAnimation;
	
	sf::FloatRect playerBoundingBox;
	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	bool isJumping;

	sf::FloatRect ground;
};

#endif	// _PLAYER_