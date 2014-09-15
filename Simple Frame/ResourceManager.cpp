#include "ResourceManager.h"
#include <cassert>
#include "DebugOut.h"


const std::string 
	ResourceManager::GRAPHICS_PATH		= "./resources/graphics/",
	ResourceManager::SOUND_PATH			= "./resources/sounds/",
	ResourceManager::MUSIC_PATH			= "./resources/music/",
	ResourceManager::FONT_PATH			= "./resources/fonts/",
	ResourceManager::LEVEL_XML_PATH		= "./resources/xml/levels/",
	ResourceManager::PROFILE_XML_PATH	= "./resources/xml/profiles/",
	ResourceManager::MENU_XML_PATH		= "./resources/xml/menus/",
	ResourceManager::CONFIG_XML_PATH	= "./resources/xml/config/";


std::map <std::string, std::unique_ptr <sf::Texture>> mTextures;
std::map <std::string, std::unique_ptr <sf::SoundBuffer>> mSoundBuffers;
std::map <std::string, std::unique_ptr <sf::Music>> mMusics;
std::map <std::string, std::unique_ptr <tinyxml2::XMLDocument>> mXML;
std::map <std::string, std::unique_ptr <sf::Font>> mFonts;


ResourceManager::ResourceManager()
{
}

void ResourceManager::destroy()
{
	// Destroy and deallocate all loaded resources
	/*
	for(auto i = mTextures.begin(); i != mTextures.end(); )
	{
		delete i->second;
		i = mTextures.erase(i);
	}

	for(auto i = mSoundBuffers.begin(); i != mSoundBuffers.end(); )
	{
		delete i->second;
		i = mSoundBuffers.erase(i);
	}

	for(auto i = mMusics.begin(); i != mMusics.end(); )
	{
		delete i->second;
		i = mMusics.erase(i);
	}

	for(auto i = mXML.begin(); i != mXML.end(); )
	{
		delete i->second;
		i = mXML.erase(i);
	}

	for(auto i = mFonts.begin(); i != mFonts.end(); )
	{
		delete i->second;
		i = mFonts.erase(i);
	}*/
}

// Fetch a sprite by getting the respective image filename
const sf::Texture& ResourceManager::getTexture(std::string fileName)
{
	if(mTextures.find(fileName) == mTextures.end())
	{
		auto newTexture = std::unique_ptr<sf::Texture>(new sf::Texture());
		if(fileName == "")
		{
			newTexture->create(0,0);			
			dbgo::println("ResourceManager.cpp: createEmptyTexture");
		}
		else
		{
			newTexture->loadFromFile(GRAPHICS_PATH + fileName);
		}
		mTextures[fileName] = std::move(newTexture);
	}

	return *mTextures[fileName];
}

// Fetch a sound by calling the respective sound filename
const sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string fileName)
{
	if(mSoundBuffers.find(fileName) == mSoundBuffers.end())
	{
		auto newSoundBuffer = std::unique_ptr<sf::SoundBuffer>(new sf::SoundBuffer());
		if(fileName != "")
		{
			newSoundBuffer->loadFromFile(SOUND_PATH + fileName);
		}
		else
		{
			dbgo::println("ResourceManager.cpp: Empty fileName! SoundBuffer");
		}
		mSoundBuffers[fileName] = std::move(newSoundBuffer);
	}

	return *mSoundBuffers[fileName];
}

// May require update/fix
// Fetch music by calling the respective music filename
sf::Music& ResourceManager::getMusic(std::string fileName)
{
	if(mMusics.find(fileName) == mMusics.end())
	{
		auto newMusic = std::unique_ptr<sf::Music>(new sf::Music());
		bool success = newMusic->openFromFile(MUSIC_PATH + fileName);
		assert(success);
		mMusics[fileName] = std::move(newMusic);
	}

	return *mMusics[fileName];
}

const tinyxml2::XMLDocument& ResourceManager::getLevelXML(std::string fileName)
{
	return getXML(LEVEL_XML_PATH, fileName);
}

const tinyxml2::XMLDocument& ResourceManager::getProfileXML(std::string fileName)
{
	// TODO: ensure that we do not deliver a stale file!
	return getXML(PROFILE_XML_PATH, fileName);
}

const tinyxml2::XMLDocument& ResourceManager::getMenuXML(std::string fileName)
{
	return getXML(MENU_XML_PATH, fileName);
}

const tinyxml2::XMLDocument& ResourceManager::getConfigXML(std::string fileName)
{
	return getXML(CONFIG_XML_PATH, fileName);
}

const sf::Font& ResourceManager::getFont(std::string fileName)
{
	if(mFonts.find(fileName) == mFonts.end())
	{
		auto newFont = std::unique_ptr<sf::Font>(new sf::Font());
		newFont->loadFromFile(FONT_PATH + fileName);
		mFonts[fileName] = std::move(newFont);
	}

	return *mFonts[fileName];
}

const tinyxml2::XMLDocument& ResourceManager::getXML(std::string path, std::string fileName)
{
	if(mXML.find(fileName) == mXML.end())
	{
		auto newXML = std::unique_ptr<tinyxml2::XMLDocument>(new tinyxml2::XMLDocument());
		const std::string filepath = path + fileName + ".xml";
		tinyxml2::XMLError retVal = newXML->LoadFile(filepath.c_str());
		if(retVal != tinyxml2::XML_NO_ERROR)
		{
			dbgo::println("ResourceManager: Error loading XML document " + filepath);
			assert(false);
			std::exit(retVal);
		}
		mXML[fileName] = std::move(newXML);
	}

	return *mXML[fileName];
}