//Class for universal sound
//Author: Ondrej Kuzela
#include "stdafx.h"
#include "SoundSource.h"
#include "AudioRenderer.h"

SoundSource::SoundSource(string name, string filename, Position* p){
	position = new Position(p);
	sound = (AudioRenderer::Instance())->loadTDSFX(filename, name, position);
	channel = (AudioRenderer::Instance())->getNew3DChannel();
}

SoundSource::~SoundSource(){
	delete sound;
}

void SoundSource::playSound(){
	(AudioRenderer::Instance())->playTDSFX(sound, channel, position);
}