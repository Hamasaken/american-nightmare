#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Accessories.h"

// Path to files
#define PATH_TO_SFX	"../Zedit/Stuff/Sound/SFX/"
#define PATH_TO_MUSIC	"../Zedit/Stuff/Sound/Music/"

// The maximum capicity of SFX and Songs
#define SFX_CAPACITY	50
#define SONG_CAPACITY	50

// Volume of Music and SFX
#define VOLUME_MUSIC	20
#define VOLUME_SFX	100

// Turn Music & SFX on/off
#define MUSIC_ON	false	
#define SFX_ON		false

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
	// \brief Stops the current music and plays new song
	// \param song The num name of the new Song
	////////////////////////////////////////////////////////////
	void switchToMusic(SONG song);

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

	int getVolumeMusic() const;
	int getVolumeEffect() const;
private:
	////////////////////////////////////////////////////////////
	// \brief Creates a random float between two float values
	// \param low The minimum value
	// \param high The maximum value
	////////////////////////////////////////////////////////////
	float getRandomFloat(float low, float high);

	int		volumeMusic;
	int		volumeEffect;
	int		nrOfMusicPlayingCurrently;

	sf::Listener	listener;			//< The listener for sfx
	sf::SoundBuffer buffer[SFX_CAPACITY];		//< The buffers of all sounds to load in sound
	sf::Sound	sfx[SFX_CAPACITY];		//< Array with sfx
	sf::Music	song[SONG_CAPACITY];		//< Array with songs
	int		nrOfSound;			//< The current number of the bufferloading
};

#endif // !SFXMANAGER_H