#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include "tinyxml2.h"

#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Music.hpp>

#include <map>
#include <string>
#include <memory>

class ResourceManager
{
public:
	static void destroy();
	const static sf::Texture& getTexture(std::string fileName);
	const static sf::SoundBuffer& getSoundBuffer(std::string fileName);
	static sf::Music& getMusic(std::string fileName);
	const static tinyxml2::XMLDocument& getLevelXML(std::string fileName);
	const static tinyxml2::XMLDocument& getProfileXML(std::string fileName);
	const static tinyxml2::XMLDocument& getMenuXML(std::string fileName);
	const static tinyxml2::XMLDocument& getConfigXML(std::string fileName);
	const static sf::Font& getFont(std::string fileName);

private:
	ResourceManager();
	const static tinyxml2::XMLDocument& getXML(std::string path, std::string fileName);
	static std::map <std::string, std::unique_ptr <sf::Texture>> mTextures;
	static std::map <std::string, std::unique_ptr <sf::SoundBuffer>> mSoundBuffers;
	static std::map <std::string, std::unique_ptr <sf::Music>> mMusics;
	static std::map <std::string, std::unique_ptr <tinyxml2::XMLDocument>> mXML;
	static std::map <std::string, std::unique_ptr <sf::Font>> mFonts;
	static const std::string GRAPHICS_PATH, SOUND_PATH, MUSIC_PATH, FONT_PATH, LEVEL_XML_PATH, PROFILE_XML_PATH, MENU_XML_PATH, CONFIG_XML_PATH;
};

#endif // _RESOURCE_MANAGER_