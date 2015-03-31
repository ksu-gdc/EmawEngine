//AssetManager for sound library
//Author: Ondrej Kuzela

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include "AudioEasyAccess.h"

using namespace std;

bool AudioEasyAccess::instanceFlag = false;
AudioEasyAccess* AudioEasyAccess::instance = NULL;

AudioEasyAccess::AudioEasyAccess()
{
}

// Returns the instance of our AudioEasyAccess
AudioEasyAccess* AudioEasyAccess::getInstance() {
	if (!instanceFlag)
	{
		instance = new AudioEasyAccess();
		instanceFlag = true;
	}
	return instance;
}

//Method for playing music
void AudioEasyAccess::playMusic(string name, string filename){
	am->add(name, filename);
	ar->loadAndPlayMusic(name, am);
}

//Method for pause/unpause music
bool AudioEasyAccess::pauseMusic(){
	return ar->pauseMusic();
}

//Method for mute/unmute music
bool AudioEasyAccess::muteMusic(){
	return ar->muteMusic();
}

//Method for stopping music
bool AudioEasyAccess::stopMusic(){
	return ar->stopMusic();
}

//Method for playing SFX
void AudioEasyAccess::playSFX(string name, string filename){
	am->add(name, filename);
	ar->loadAndPlaySFX(name, am);
}

//Method for turning the volume of music up
bool AudioEasyAccess::musicVolumeUp(){
	return ar->musicVolumeUp();
}

//Method for turning the volume of music down
bool AudioEasyAccess::musicVolumeDown(){
	return ar->musicVolumeDown();
}

//Method for mute/unmute SFX
bool AudioEasyAccess::muteSFX(){
	return ar->muteSFX();
}

//Method for turning the volume of SFX up
bool AudioEasyAccess::SFXVolumeUp(){
	return ar->SFXVolumeUp();
}

//Method for turning the volume of SFX down
bool AudioEasyAccess::SFXVolumeDown(){
	return ar->SFXVolumeDown();
}

//Method for getting SoundSource object
SoundSource* AudioEasyAccess::getSoundSource(string name, string filename, float x, float y, float z){
	return new SoundSource(name, filename, new Position(x, y, z));
}