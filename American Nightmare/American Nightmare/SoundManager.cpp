#include "SoundManager.h"

SoundManager::SoundManager()
{
//	listener.setGlobalVolume(100);
	volumeEffect = VOLUME_SFX;
	volumeMusic = VOLUME_MUSIC;

	nrOfSound = NULL;

	printf("%s", "Just ignore this for now, ok?\n");

//	loadSFXs();
//	loadSongs();
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
//	sfx[SFX_PROP] = loadSFX(pathToFolder + "sfx.wav");
	// SFX 2
	// SFX 3

	// Setting every sfx at deicided volume
	for (sf::Sound& s : sfx)
		s.setVolume(volumeEffect);
}

void SoundManager::loadSongs()
{
	std::string pathToFolder = MUSIC_PATH;

	// Load all songs here
//	song[MUSIC_PROP].openFromFile(pathToFolder + "music.ogg");
	// SONG 2
	// SONG 3

	// Setting every song as looping and setting volume
	for (sf::Music& m : song)
	{
		m.setLoop(true);
		m.setVolume(volumeMusic);
	}
}

void SoundManager::stopSFX(SFX effect)
{
	if (SFX_ON)
	{
		int nrOfSFX = static_cast<int>(effect);

		if (sfx[nrOfSFX].getStatus() == sf::Sound::Status::Playing)
			sfx[nrOfSFX].stop();
	}
}

void SoundManager::playSFX(SFX effect)
{
	if (SFX_ON)
	{
		int nrOfSFX = static_cast<int>(effect);

		sfx[nrOfSFX].setPitch(1);
		sfx[nrOfSFX].play();
	}
}

void SoundManager::playModifiedSFX(SFX effect, float volume, float offset)
{
	if (SFX_ON)
	{
		int nrOfSFX = static_cast<int>(effect);

		sfx[nrOfSFX].setVolume(volume);
		sfx[nrOfSFX].setPitch(getRandomFloat(1 - offset, 1 + offset));
		sfx[nrOfSFX].play();
	}
}

void SoundManager::playSong(SONG song)
{
	if (MUSIC_ON)
	{
		int nrOfSong = static_cast<int>(song);
		this->nrOfMusicPlayingCurrently = nrOfSong;

		this->song[nrOfSong].play();
	}
}

void SoundManager::switchToMusic(SONG song)
{
	if (MUSIC_ON)
	{
		if (int(song) != nrOfMusicPlayingCurrently)
		{
			pauseMusic();
			playSong(song);
		}
	}
}

void SoundManager::stopMusic()
{
	if (MUSIC_ON)
	{
		if (song[nrOfMusicPlayingCurrently].getStatus() == sf::Sound::Status::Playing)
			song[nrOfMusicPlayingCurrently].stop();
	}
}

void SoundManager::pauseMusic()
{
	if (MUSIC_ON)
	{
		if (song[nrOfMusicPlayingCurrently].getStatus() == sf::Sound::Status::Playing)
			song[nrOfMusicPlayingCurrently].pause();
	}
}

void SoundManager::continueMusic()
{
	if (MUSIC_ON)
	{
		if (song[nrOfMusicPlayingCurrently].getStatus() == sf::Sound::Status::Paused)
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