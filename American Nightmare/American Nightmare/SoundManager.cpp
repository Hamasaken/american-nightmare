#include "SoundManager.h"

SoundManager::SoundManager()
{
	// Setting listener volume
	nrOfMusicPlayingCurrently = -1;

	listener.setGlobalVolume(100);

	// Setting volumes
	volumeEffect = VOLUME_SFX;
	volumeMusic = VOLUME_MUSIC;

	nrOfSound = NULL;

	// Load stuff
	loadSFXs();
	loadSongs();
}

SoundManager::SoundManager(const SoundManager& other) { }

SoundManager::~SoundManager() { }

sf::Sound SoundManager::loadSFX(std::string path)
{
	// Load a specific SFX
	if (!buffer[nrOfSound].loadFromFile(path))
		std::runtime_error("Could not load SFX from path: " + path);
	else nrOfSound++;

	return sf::Sound(buffer[nrOfSound - 1]);
}

void SoundManager::loadSFXs()
{
	std::string pathToFolder = SFX_PATH;

	// Load every SFX here
	sfx[SFX_BIP] = loadSFX(pathToFolder + "sfx_bip.wav");
	sfx[SFX_HIT] = loadSFX(pathToFolder + "sfx_hit.wav");
	sfx[SFX_POWERUP] = loadSFX(pathToFolder + "sfx_powerup.wav");

	// Setting every sfx at deicided volume
	for (sf::Sound& s : sfx)
		s.setVolume(volumeEffect);
}

void SoundManager::loadSongs()
{
	std::string pathToFolder = MUSIC_PATH;

	// Load all songs here
	song[MUSIC_WOOP].openFromFile(pathToFolder + "woop.ogg");
	song[MUSIC_BOOGIE].openFromFile(pathToFolder + "boogie.ogg");

	// Setting every song as looping and setting volume
	for (sf::Music& m : song)
	{
		m.setLoop(true);
		m.setVolume(volumeMusic);
	}
}

void SoundManager::stopSFX(SFX effect)
{
	if (SFX_ON && sfx[effect].getStatus() == sf::Sound::Playing)
	{
		sfx[effect].stop();
	}
}

void SoundManager::playSFX(SFX effect)
{
	if (SFX_ON && sfx[effect].getStatus() != sf::Sound::Playing)
	{
		sfx[effect].setPitch(1);
		sfx[effect].play();
	}
}

void SoundManager::playModifiedSFX(SFX effect, float volume, float offset)
{
	if (SFX_ON && sfx[effect].getStatus() != sf::Sound::Playing)
	{
		sfx[effect].setVolume(volume);
		sfx[effect].setPitch(getRandomFloat(1 - offset, 1 + offset));
		sfx[effect].play();
	}
}

void SoundManager::playSong(SONG song)
{
	if (MUSIC_ON)
	{
		if (nrOfMusicPlayingCurrently != -1)
		{
			if (this->song[nrOfMusicPlayingCurrently].getStatus() == sf::Sound::Playing)
				pauseMusic();
		}

		nrOfMusicPlayingCurrently = song;
		this->song[nrOfMusicPlayingCurrently].play();
	}
}

void SoundManager::stopMusic()
{
	if (MUSIC_ON && nrOfMusicPlayingCurrently != -1)
	{
		if (song[nrOfMusicPlayingCurrently].getStatus() == sf::Sound::Playing)
			song[nrOfMusicPlayingCurrently].stop();
	}
}

void SoundManager::pauseMusic()
{
	if (MUSIC_ON && nrOfMusicPlayingCurrently != -1)
	{
		if (song[nrOfMusicPlayingCurrently].getStatus() == sf::Sound::Playing)
			song[nrOfMusicPlayingCurrently].pause();
	}
}

void SoundManager::continueMusic()
{
	if (MUSIC_ON && nrOfMusicPlayingCurrently != -1)
	{
		if (song[nrOfMusicPlayingCurrently].getStatus() == sf::Sound::Paused)
			song[nrOfMusicPlayingCurrently].play();
	}
}

void SoundManager::changeVolume(int volumeMusic, int volumeEffect)
{
	this->volumeMusic = volumeMusic;
	this->volumeEffect = volumeEffect;
}

int SoundManager::getVolumeMusic() const { return volumeMusic; }
int SoundManager::getVolumeEffect() const { return volumeEffect; }

float SoundManager::getRandomFloat(float low, float high)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}