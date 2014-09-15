#include "Projectile.h"


Projectile::Projectile(sf::Vector2f spawnPosition) :
	mPosition(spawnPosition)
{
}


Projectile::~Projectile()
{
}

void Projectile::update()
{
	
}

void Projectile::killEntity()
{
	mIsAlive = false;
}

bool Projectile::getLiveState()
{
	return mIsAlive;
}

const sf::Vector2f& Projectile::getPosition() const
{
	return mPosition;
}

sf::FloatRect Projectile::getBoundingBox()
{
	return mSprite.getGlobalBounds();
}