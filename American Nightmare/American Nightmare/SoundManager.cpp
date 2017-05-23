#include "SoundManager.h"

SoundManager::SoundManager()
{
	nrOfMusicPlayingCurrently = -1;
	nrOfSound = NULL;

	// Setting volumes
	volumeEffect = VOLUME_SFX;
	volumeMusic = VOLUME_MUSIC;

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
	sfx[SFX_BTN] = loadSFX(pathToFolder + "sfx_btn.wav");
	sfx[SFX_LtoR] = loadSFX(pathToFolder + "sfx_leftToRight.wav");
	sfx[SFX_RtoL] = loadSFX(pathToFolder + "sfx_rightToLeft.wav");
	sfx[SFX_SUCTION] = loadSFX(pathToFolder + "sfx_suction.wav");
	sfx[SFX_FIRE] = loadSFX(pathToFolder + "sfx_fire.ogg");

	// Setting every sfx at deicided volume
	for (sf::Sound& s : sfx)
		s.setVolume(volumeEffect);
}

void SoundManager::loadSongs()
{
	std::string pathToFolder = MUSIC_PATH;

	// Load all songs here
	song[URANIUM_FEVER].openFromFile(pathToFolder + "Uranium Fever.ogg");
	song[GOOD_ROCKIN_TONIGHT].openFromFile(pathToFolder + "Good Rockin Tonight.ogg");

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

void SoundManager::playSFXOverDrive(SFX effect, float offset)
{
	if (SFX_ON)
	{
		sfx[effect].setPitch(1);
		sfx[effect].setPitch(getRandomFloat(1 - offset, 1 + offset));
		sfx[effect].play();
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

void SoundManager::mute()
{
	if (volumeEffect != 0 && volumeEffect != 0)
	{
		stopSFX(SFX(nrOfMusicPlayingCurrently));
		pauseMusic();
		this->volumeMusic = 0;
		this->volumeEffect = 0;
		listener.setGlobalVolume(0);
	}
	else
	{
		this->volumeMusic = VOLUME_MUSIC;
		this->volumeEffect = VOLUME_SFX;
		listener.setGlobalVolume(100);
		continueMusic();
	}

	for (sf::Music& m : song)
		m.setVolume(volumeMusic);
	for (sf::Sound& s : sfx)
		s.setVolume(volumeEffect);
}

int SoundManager::getVolumeMusic() const { return volumeMusic; }
int SoundManager::getVolumeEffect() const { return volumeEffect; }

float SoundManager::getRandomFloat(float low, float high)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}