#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Accessories.h"

// The maximum capicity of SFX and Songs
#define SFX_CAPACITY	30
#define SONG_CAPACITY	30

// Volume of Music and SFX
#define VOLUME_MUSIC	50
#define VOLUME_SFX		70

// Turn Music & SFX on/off
#define MUSIC_ON		true	
#define SFX_ON			true

class SoundManager
{
public:
	// Put sfx names here, and then load them in the loadSFXs function
	enum SFX
	{
		SFX_BIP, 
		SFX_HIT,
		SFX_POWERUP,
		SFX_BTN,
		SFX_LtoR,
		SFX_RtoL,
		SFX_SUCTION,
		SFX_FIRE,
		SFX_STEPS, 
		SFX_BIRDS,
		SFX_SHOCKWAVE,
		SFX_ZOMBIE_1,
		SFX_ZOMBIE_2, 
		SFX_DASH,
		SFX_JUMP,
		SFX_HURT, 
		SFX_HOVER, 
		SFX_LASER, 
		SFX_DEATH
	};

	// Put song names here, and then load them in the loadSongs functions
	enum SONG
	{
		FOX_BOOGIE,
		URANIUM_FEVER,
		GOOD_ROCKIN_TONIGHT, 
		JAZZY_INTERLUDE
	};

	SoundManager();
	SoundManager(const SoundManager& other);
	~SoundManager();

	////////////////////////////////////////////////////////////
	// \brief Constructs a sf::Sound from file
	// \param path The file path to the SFX 
	// \return Returns the sound file as a sf::Sound
	////////////////////////////////////////////////////////////
	sf::Sound loadSFX(std::string path);

	////////////////////////////////////////////////////////////
	// \brief Loads every song 
	////////////////////////////////////////////////////////////
	void loadSongs();

	////////////////////////////////////////////////////////////
	// \brief Calls LoadSFX for every SFX
	////////////////////////////////////////////////////////////
	void loadSFXs();

	////////////////////////////////////////////////////////////
	// \brief Stops a specific SFX from playing
	// \param effect The enum name of the SFX
	////////////////////////////////////////////////////////////
	void stopSFX(SFX effect);

	////////////////////////////////////////////////////////////
	// \brief Plays another SFX even though one is already playing
	// \param effect The enum name of the SFX
	// \param offset The offset max/min of the volume (0:100)
	// \param offset The offset max/min of the pitchchange (0:1)
	////////////////////////////////////////////////////////////
	void playSFXOverDrive(SFX effect, float volume = 100.f, float offset = 0.1f);

	////////////////////////////////////////////////////////////
	// \brief Plays a specific SFX
	// \param effect The enum name of the SFX
	////////////////////////////////////////////////////////////
	void playSFX(SFX effect);

	////////////////////////////////////////////////////////////
	// \brief Plays a specific SFX with random pitch change,
	//		good for stuff like foot-steps
	// \param effect The enum name of the SFX
	// \param volume The volume of the SFX 
	// \param offset The offset max/min of the pitchchange (0:1)
	////////////////////////////////////////////////////////////
	void playModifiedSFX(SFX effect, float volume, float offset);

	////////////////////////////////////////////////////////////
	// \brief Plays a specific Song
	// \param song The enum name of the Song
	////////////////////////////////////////////////////////////
	void playSong(SONG song);

	////////////////////////////////////////////////////////////
	// \brief Stops the current music
	////////////////////////////////////////////////////////////
	void stopMusic();

	////////////////////////////////////////////////////////////
	// \brief Pauses the current music
	////////////////////////////////////////////////////////////
	void pauseMusic();

	////////////////////////////////////////////////////////////
	// \brief Continues the current music
	////////////////////////////////////////////////////////////
	void continueMusic();

	////////////////////////////////////////////////////////////
	// \brief Changes the listeners volume
	////////////////////////////////////////////////////////////
	void changeVolume(int volumeMusic, int volumeEffect);
	
	////////////////////////////////////////////////////////////
	// \brief Mutes/Unmutes
	////////////////////////////////////////////////////////////
	void mute();

	int getVolumeMusic() const;
	int getVolumeEffect() const;
private:
	////////////////////////////////////////////////////////////
	// \brief Creates a random float between two float values
	// \param low The minimum value
	// \param high The maximum value
	////////////////////////////////////////////////////////////
	float getRandomFloat(float low, float high);

	int				volumeMusic;
	int				volumeEffect;
	int				nrOfMusicPlayingCurrently;
	sf::Listener	listener;
	sf::SoundBuffer buffer[SFX_CAPACITY];		//< The buffers of all sounds to load in sound
	sf::Sound		sfx[SFX_CAPACITY];		//< Array with sfx
	sf::Music		song[SONG_CAPACITY];		//< Array with songs
	int				nrOfSound;			//< The current number of the bufferloading
};

#endif // !SFXMANAGER_H
