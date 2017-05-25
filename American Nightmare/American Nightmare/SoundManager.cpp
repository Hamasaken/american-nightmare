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
	sfx[SFX_STEPS] = loadSFX(pathToFolder + "sfx_footsteps.wav");
	sfx[SFX_BIRDS] = loadSFX(pathToFolder + "sfx_birds.ogg");
	sfx[SFX_SHOCKWAVE] = loadSFX(pathToFolder + "sfx_shockwave.ogg");
	sfx[SFX_LASER] = loadSFX(pathToFolder + "sfx_laser.wav");
	sfx[SFX_ZOMBIE_1] = loadSFX(pathToFolder + "sfx_zombie_1.wav");
	sfx[SFX_ZOMBIE_2] = loadSFX(pathToFolder + "sfx_zombie_2.wav");
	sfx[SFX_DASH] = loadSFX(pathToFolder + "sfx_dash.wav");
	sfx[SFX_JUMP] = loadSFX(pathToFolder + "sfx_jump.wav");
	sfx[SFX_HURT] = loadSFX(pathToFolder + "sfx_hurt.ogg");
	sfx[SFX_HOVER] = loadSFX(pathToFolder + "sfx_hover.wav");
	sfx[SFX_DEATH] = loadSFX(pathToFolder + "sfx_death.wav");

	// Setting every sfx at deicided volume
	for (sf::Sound& s : sfx)
		s.setVolume(volumeEffect);
}

void SoundManager::loadSongs()
{
	std::string pathToFolder = MUSIC_PATH;

	// Load all songs here
	song[FOX_BOOGIE].openFromFile(pathToFolder + "Fox Boogie.ogg");
	song[URANIUM_FEVER].openFromFile(pathToFolder + "Uranium Fever.ogg");
	song[GOOD_ROCKIN_TONIGHT].openFromFile(pathToFolder + "Good Rockin Tonight.ogg");
	song[JAZZY_INTERLUDE].openFromFile(pathToFolder + "Jazzy Interlude.ogg");

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
		sfx[effect].stop();
	}
}

void SoundManager::playSFXOverDrive(SFX effect, float volume, float offset)
{
	if (SFX_ON)
	{
		sfx[effect].setVolume(volume);
		sfx[effect].setPitch(getRandomFloat(1 - offset, 1 + offset));
		sfx[effect].play();
	}
}

void SoundManager::playSFX(SFX effect)
{
	if (SFX_ON)
	{
		if (sfx[effect].getStatus() != sf::Sound::Status::Playing)
		{
			sfx[effect].setPitch(1);
			sfx[effect].play();
		}
	}
}

void SoundManager::playModifiedSFX(SFX effect, float volume, float offset)
{
	if (SFX_ON)
	{
		if (sfx[effect].getStatus() != sf::Sound::Status::Playing)
		{
			sfx[effect].setVolume(volume);
			sfx[effect].setPitch(getRandomFloat(1 - offset, 1 + offset));
			sfx[effect].play();
		}
	}
}

void SoundManager::playSong(SONG song)
{
	if (MUSIC_ON)
	{
		if (nrOfMusicPlayingCurrently != -1 && nrOfMusicPlayingCurrently != song)
		{
			stopMusic();
		}

		if (nrOfMusicPlayingCurrently != song)
		{
			nrOfMusicPlayingCurrently = song;
			this->song[nrOfMusicPlayingCurrently].play();
		}
	}
}

void SoundManager::stopMusic()
{
	if (MUSIC_ON)
	{
		song[nrOfMusicPlayingCurrently].stop();
	}
}

void SoundManager::pauseMusic()
{
	if (MUSIC_ON)
	{
		song[nrOfMusicPlayingCurrently].pause();
	}
}

void SoundManager::continueMusic()
{
	if (MUSIC_ON)
	{
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