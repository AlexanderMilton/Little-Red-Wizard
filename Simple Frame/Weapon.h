#ifndef _WEAPON_
#define _WEAPON_

#include "EntityManager.h"

#include <SFML\System\Clock.hpp>

class Weapon
{
public:
	Weapon();
	~Weapon();
	void fire(sf::Vector2f& origin, EntityManager& entityManager);

private:
	sf::Clock mReloadTimer;
	bool mIsReloading;
	//sf::Vector2f;
};

#endif	// _WEAPON_