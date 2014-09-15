#ifndef _PROJECTILE_ 
#define _PROJECTILE_

#include "Entity.h"

#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Sprite.hpp"

class Projectile : public Entity

{

public:
	Projectile(sf::Vector2f spawnPosition);
	~Projectile();

	void update() override;
	void draw();
	void killEntity() override;
	bool getLiveState() override;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getBoundingBox();

private:
	sf::Vector2f mPosition;
	bool mIsAlive;
	sf::Sprite mSprite;
};

#endif	// _PROJECTILE_
