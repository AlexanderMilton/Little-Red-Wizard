#include "SoundEngine.h"
#include "ResourceManager.h" // delete if not used
#include "DebugOut.h"

#include <cassert>

std::map <std::string, sf::Music*> SoundEngine::mMusic;
std::map <std::string, sf::Sound*> SoundEngine::mSoundEffects;
sf::Music* SoundEngine::currentSong = nullptr;

float SoundEngine::mMusicVolume = 100.0f;
float SoundEngine::mSoundVolume = 100.0f;

// No loose ends - delete and deallocaate the stored sounds (music is destroyed by resource manager)
void SoundEngine::destroy()
{
	for (auto i = mSoundEffects.begin(); i != mSoundEffects.end(); )
	{
		delete i->second;
		i = mSoundEffects.erase(i);
	}
}


// Continue playing all stopped or paused sounds
void SoundEngine::resumeAll()
{
	resumeAllSoundEffects();
	resumeAllMusic();
}

// Pause all sounds (including music)
void SoundEngine::pauseAll()
{
	pauseAllSoundEffects();
	pauseAllMusic();
}

// Stop all sounds (including music)
void SoundEngine::stopAll()
{
	stopAllSoundEffects();
	stopAllMusic();
}


// Fetch the sound effect you wish to load, use the full file name as parameter.
void SoundEngine::fetchSoundEffect(std::string fileName)
{
		dbgo::println("SoundEngine.cpp: Fetching Sound Effect (" + fileName + ") from Resource Manager");
		sf::Sound* fetchedSound = new sf::Sound(ResourceManager::getSoundBuffer(fileName));
		mSoundEffects[fileName] = fetchedSound;
}

// Play sound effect. Use the full file name of the sound effect as parameter.
void SoundEngine::playSoundEffect(std::string fileName)
{
	if(mSoundEffects.find(fileName) == mSoundEffects.end())
	{
		fetchSoundEffect(fileName);
	}
		
	//dbgo::println("Playing Sound Effect (" + fileName + ")");

	if (mSoundEffects[fileName]->getStatus() != sf::Sound::Status::Playing)
	{
		assert(mSoundEffects.find(fileName)->second != nullptr);
		mSoundEffects[fileName]->setVolume(mSoundVolume);
		mSoundEffects[fileName]->play();
	}
}

// Pause the current sound effect
void SoundEngine::pauseSoundEffect(std::string fileName)
{
	assert(mSoundEffects.find(fileName)->second != nullptr);
	mSoundEffects[fileName]->pause();
}



// Fetch the music you wish to load, use the full file name as parameter.
void SoundEngine::fetchMusic(std::string fileName)
{
	dbgo::println("File not loaded. Fetching Music (" + fileName + ") from Resource Manager");

	sf::Music* fetchedMusic = &(ResourceManager::getMusic(fileName));
	mMusic[fileName] = fetchedMusic;
	mMusic[fileName]->setVolume(mMusicVolume);

	assert(mMusic.find(fileName)->second != nullptr);
}

// Play or resume the currently set music.
void SoundEngine::playMusic(std::string fileName)
{
	if(mMusic.find(fileName) == mMusic.end())
	{
		fetchMusic(fileName);
	}
	
	currentSong = mMusic[fileName];

	//dbgo::println("Playing Music (" + fileName + ")");

	if (mMusic[fileName]->getStatus() != sf::Sound::Status::Playing)
	{
		assert(mMusic.find(fileName)->second != nullptr);
		mMusic[fileName]->setVolume(mMusicVolume);
		mMusic[fileName]->play();
	}
}

// Set Music Volume
void SoundEngine::setMusicVolume(float volume)
{
	assert(volume <= 100.0f && volume >= 0.0f);

	if (volume <= 100.0f && volume >= 0.0f)
	{
		mMusicVolume = volume;
	}

	// Pause music if muted
	if (mMusicVolume == 0)
	{
		pauseAllMusic();
	}

	// Unpause if paused and unmuted
	if (mMusicVolume > 0 && currentSong->getStatus() == sf::Sound::Paused)
	{
		resumeAllMusic();
	}

	currentSong->setVolume(mMusicVolume);
}

// Get music volume
float SoundEngine::getMusicVolume()
{
	return mMusicVolume;
}

// Set Sound Volume
void SoundEngine::setSoundVolume(float volume)
{
	assert(volume <= 100.0f && volume >= 0.0f);

	if (volume <= 100.0f && volume >= 0.0f)
	{
		mSoundVolume = volume;
	}
}

// Return Sound Volume
float SoundEngine::getSoundVolume()
{
	return mSoundVolume;
}


sf::Sound::Status SoundEngine::getSoundEffectStatus(std::string fileName)
{
	//assert(mSoundEffects.find(fileName)->second != nullptr);
	if (mSoundEffects.find(fileName)->second != nullptr)
	{
		return (mSoundEffects.find(fileName)->second->getStatus());
	}
	else
	{
		dbgo::println("Error getting sound effect status, the file name could not be found");
	}
}

sf::Sound::Status SoundEngine::getMusicStatus(std::string fileName)
{
	//assert(mMusic.find(fileName)->second != nullptr);
	if (mMusic.find(fileName)->second != nullptr)
	{
		return (mMusic.find(fileName)->second->getStatus());
	}
	else
	{
		dbgo::println("Error getting music status, the file name could not be found");
	}
}



// ----- Private Access Functions ----- //



SoundEngine::SoundEngine()
{
}


void SoundEngine::resumeAllSoundEffects()
{
	for (auto i = mSoundEffects.begin(); i != mSoundEffects.end(); i++)
	{
		if (i->second->getStatus() == sf::Sound::Paused)
		{
			playSoundEffect(i->first);
		}
	}
}

void SoundEngine::pauseAllSoundEffects()
{
	for (auto i = mSoundEffects.begin(); i != mSoundEffects.end(); i++)
	{
		if (i->second->getStatus() == sf::Sound::Playing)
		{
			pauseSoundEffect(i->first);
		}
	}
}

void SoundEngine::stopAllSoundEffects()
{
	for (auto i = mSoundEffects.begin(); i != mSoundEffects.end(); ++i)
	{
		if (i->second->getStatus() != sf::Sound::Stopped)
		{
			stopSoundEffect(i->first);
		}
	}
}


void SoundEngine::resumeAllMusic()
{	
	for (auto i = mMusic.begin(); i != mMusic.end(); ++i)
	{
		if (i->second->getStatus() == sf::Music::Paused)
		{
			playMusic(i->first);
		}
	}
}

void SoundEngine::pauseAllMusic()
{
	for (auto i = mMusic.begin(); i != mMusic.end(); ++i)
	{
		if (i->second->getStatus() == sf::Music::Playing)
		{
			pauseMusic(i->first);
		}
	}
}

void SoundEngine::stopAllMusic()
{
	for (auto i = mMusic.begin(); i != mMusic.end(); ++i)
	{
		if (i->second->getStatus() == sf::Music::Playing)
		{
			stopMusic(i->first);
		}
	}
}


// Stop the current sound effect
void SoundEngine::stopSoundEffect(std::string fileName)
{
	assert(mSoundEffects.find(fileName)->second != nullptr);
	mSoundEffects[fileName]->stop();
}

// Delete the current sound effect
void SoundEngine::deleteSoundEffect(std::string fileName)
{
	assert(mSoundEffects.find(fileName)->second != nullptr);
	delete mSoundEffects[fileName];
	mSoundEffects.erase(fileName);
}


// Stop the music, but keep it in memory.
void SoundEngine::stopMusic(std::string fileName)
{
	dbgo::println("Stopping Music: " + fileName);
	
	assert(mMusic.find(fileName)->second != nullptr);
	mMusic[fileName]->stop();
}

// Pause the music. Use playMusic() to resume.
void SoundEngine::pauseMusic(std::string fileName)
{
	dbgo::println("Pausing Music: " + fileName);

	assert(mMusic.find(fileName)->second != nullptr);
	mMusic[fileName]->pause();
}

// Delete the current music from the memory.
void SoundEngine::deleteMusic(std::string fileName)
{
	dbgo::println("Deleting Music: " + fileName);
	
	assert(mMusic.find(fileName)->second != nullptr);
	delete mMusic[fileName];
	mMusic.erase(fileName);
}
