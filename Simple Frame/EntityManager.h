#ifndef _ENTITY_MANAGER_
#define _ENTITY_MANAGER_

#include "Entity.h"
#include "Projectile.h"

#include <vector>
#include <memory>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	static void destroy();
	static void fireProjectile(sf::Vector2f position);

private:
};

#endif	// _ENTITY_MANAGER_