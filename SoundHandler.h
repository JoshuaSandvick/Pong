#include <SDL_mixer.h>
#include <string>
#pragma once
class SoundHandler
{
public:
	SoundHandler(bool isMusicNotSound, std::string filename);
	SoundHandler();
	~SoundHandler();

	//Sets the sound file
	void setSound(bool isMusicNotSound, std::string filename);

	//Plays sound
	void playSound();

	//Plays music
	void playMusic();

private:

	//The music track (If handler is for music)
	Mix_Music* musicTrack = NULL;

	//The sound track (If handler is for sound effects)
	Mix_Chunk* soundEffect = NULL;

};

