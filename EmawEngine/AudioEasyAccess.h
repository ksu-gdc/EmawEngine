//Class for easy access to sound features
//Author: Ondrej Kuzela

#pragma once
#include <string>
#include <map>
#include "Utils.h"
#include "Position.h"
#include "SoundSource.h"
#include "AudioManager.h"
#include "AudioRenderer.h"

class AudioEasyAccess{
private:
	AudioEasyAccess();

	// Statics
	static bool instanceFlag;
	static AudioEasyAccess *instance;
	AudioManager* am = AudioManager::getInstance();
	AudioRenderer* ar = AudioRenderer::Instance();

public:

	// Singleton accessor
	static AudioEasyAccess* getInstance();

	//Method for playing music
	void playMusic(string name, string filename);

	//Method for pause/unpause music
	bool pauseMusic();

	//Method for mute/unmute music
	bool muteMusic();

	//Method for stopping music
	bool stopMusic();

	//Method for playing SFX
	void playSFX(string name, string filename);

	//Method for turning the volume of music up
	bool musicVolumeUp();

	//Method for turning the volume of music down
	bool musicVolumeDown();

	//Method for mute/unmute SFX
	bool muteSFX();

	//Method for turning the volume of SFX up
	bool SFXVolumeUp();

	//Method for turning the volume of SFX down
	bool SFXVolumeDown();

	//Method for getting SoundSource object
	SoundSource* getSoundSource(string name, string filename, float x, float y, float z);
};