#ifndef _ENTITY_
#define _ENTITY_

#include "SFML\Graphics\RenderWindow.hpp"

#include <memory>

class Entity

{
public:
	Entity();
	~Entity();

	virtual void update() = 0;
	virtual void draw(std::unique_ptr <sf::RenderWindow> window);
	virtual void killEntity() = 0;
	virtual bool getLiveState() = 0;
};

#endif	// _ENTITY_
