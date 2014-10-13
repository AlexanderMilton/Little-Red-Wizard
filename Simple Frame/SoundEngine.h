#ifndef _SOUND_ENGINE_
#define _SOUND_ENGINE_

#include <map>
#include <memory>

#include "SFML\Audio.hpp"

class SoundEngine
{
public:
	static void destroy();

	static void resumeAll();
	static void pauseAll();
	static void stopAll();
	
	static void fetchSoundEffect(std::string fileName);
	static void playSoundEffect(std::string fileName);
	static void pauseSoundEffect(std::string fileName);
	
	static void fetchMusic(std::string fileName);
	static void playMusic(std::string fileName);
	static void setMusicVolume(float volume);
	static float getMusicVolume();

	static void setSoundVolume(float volume);
	static float getSoundVolume();
	
	
	static sf::Sound::Status getSoundEffectStatus(std::string fileName);
	static sf::Sound::Status getMusicStatus(std::string fileName);

private:
	SoundEngine();

	static void resumeAllSoundEffects();
	static void pauseAllSoundEffects();
	static void stopAllSoundEffects();

	static void resumeAllMusic();
	static void pauseAllMusic();
	static void stopAllMusic();


	static void stopSoundEffect(std::string fileName);
	static void deleteSoundEffect(std::string fileName);
	
	static void stopMusic(std::string fileName);
	static void pauseMusic(std::string fileName);
	static void deleteMusic(std::string fileName);


	static std::map <std::string, std::shared_ptr<sf::Music>> mMusic;
	static std::map <std::string, std::shared_ptr<sf::Sound>> mSoundEffects;
	static std::shared_ptr<sf::Music> currentSong;

	static float mMusicVolume;
	static float mSoundVolume;
};

#endif	// _SOUND_ENGINE_