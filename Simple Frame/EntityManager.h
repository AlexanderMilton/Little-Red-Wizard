#ifndef _ENTITY_MANAGER_
#define _ENTITY_MANAGER_

#include "Entity.h"
#include "Projectile.h"

#include <vector>
#include <memory>

/*
* Handles the creation and destruction of loose entities such as projectiles and enemies.
* Detects and handles collision between entities and the player.
*/

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	void destroy();
	void fireProjectile(sf::Vector2f position);

private:
	std::vector <std::unique_ptr<Entity>> mEntityVector;

};

#endif	// _ENTITY_MANAGER_