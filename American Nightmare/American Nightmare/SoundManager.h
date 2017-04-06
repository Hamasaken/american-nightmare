#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Accessories.h"

// Path to files
#define PATH_TO_SFX "../Zedit/Stuff/Sound/SFX/"
#define PATH_TO_MUSIC "../Zedit/Stuff/Sound/Music/"

// The maximum capicity of SFX and Songs
#define SFX_CAPACITY		50
#define SONG_CAPACITY		50

// Volume of Music and SFX
#define VOLUME_MUSIC		20
#define VOLUME_SFX			100

// Turn Music & SFX on/off
#define MUSIC_ON			false	
#define SFX_ON				false

class SoundManager
{
public:
	// Put sfx names here, and then load them in the loadSFXs function
	enum SFX
	{
		JUMP
	};

	// Put song names here, and then load them in the loadSongs functions
	enum SONG
	{
		ROARING_20
	};

	SoundManager();
	SoundManager(const SoundManager& other);
	~SoundManager();

	sf::Sound loadSFX(std::string path);
	void loadSongs();
	void loadSFXs();

	void stopSFX(SFX effect);
	void playSFX(SFX effect);
	void playModifiedSFX(SFX effect, float volume);
	void playPitchedSFX(SFX effect, float offset);
	void playBothSFX(SFX effect, float volume, float offset);

	void playSong(SONG song);
	void switchToMusic(SONG song);
	void stopMusic();
	void pauseMusic();
	void continueMusic();

	void changeVolume(int volumeMusic, int volumeEffect);
	int getVolumeMusic() const;
	int getVolumeEffect() const;

private:
	float getRandomFloat(float low, float high);

	int				volumeMusic;
	int				volumeEffect;
	int				nrOfMusicPlayingCurrently;

	sf::Listener	listener;					//< The listener for sfx
	sf::SoundBuffer buffer[SFX_CAPACITY];		//< The buffers of all sounds to load in sound
	sf::Sound		sfx[SFX_CAPACITY];			//< Array with sfx
	sf::Music		song[SONG_CAPACITY];		//< Array with songs
	int				nrOfSound;					//< The current number of the bufferloading
};

#endif // !SFXMANAGER_H
