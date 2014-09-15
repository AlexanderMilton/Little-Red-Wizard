#include "EntityManager.h"


EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::destroy()
{
	// Destroy and deallocate all loaded resources

	//for (auto i = mEntityVector.begin(); i != mEntityVector.end();)
	//{
	//	delete i->second;
	//	i = mEntityVector.erase(i);
	//}
}

void EntityManager::fireProjectile(sf::Vector2f position)
{

	//auto newProjectile = std::unique_ptr<Entity>(new Projectile(sf::Vector2f(position)));

	std::vector <std::unique_ptr<Entity>> mEntityVector;

	std::unique_ptr<Entity> newProjectile = std::unique_ptr<Entity>(new Projectile(sf::Vector2f(position)));
	
	mEntityVector.push_back(std::move(newProjectile));

	
}

// vector<unique_ptr<Song>> v;

// unique_ptr<Song> pSong = unique_ptr<Song>(new Song(L"Mr. Children", L"Namonaki Uta"));

// v.push_back(unique_ptr<Song>(new Song(L"B'z", L"Juice")));

/* 

std::vector<std::unique_ptr<MyObject>> v;
auto ptr = std::unique_ptr<MyObject>(new MyObject());
v.push_back(std::move(ptr));

*/
