#include "Weapon.h"
#include "EntityManager.h"

#include <SFML\Window\Mouse.hpp>

static const float reloadTime = 100.0f;			// Milliseconds

Weapon::Weapon()
{
	mReloadTimer.restart();
}

Weapon::~Weapon()
{
}

void Weapon::fire(sf::Vector2f& origin, EntityManager& entityManager)
{
	sf::Mouse::getPosition();

	if (mReloadTimer.getElapsedTime().asMilliseconds() > reloadTime)
		mIsReloading = false;


	else
		mIsReloading = true;

	// We need a delay in the firing ability, 
	if (mIsReloading == false)
	{
		//// Check facing direction to determine the spawn origin of the projectile
		//if (mFacingLeft == true)
		//{
		//	sf::Vector2f projectileOrigin(mPosition.x, mPosition.y - (getBoundingBox().height / 2));
		//	entityManager.fireProjectile(projectileOrigin);
		//	mReloadTimer.restart();
		//}
		//if (mFacingLeft == false)
		//{
		//	sf::Vector2f projectileOrigin(sf::Vector2f(mPosition.x + (getBoundingBox().width), mPosition.y - (getBoundingBox().height / 2)));
		//	entityManager.fireProjectile(projectileOrigin);
		//	mReloadTimer.restart();
		//}
	}
}