//Testing class for playing music
//Author: Ondrej Kuzela

#include "stdafx.h"
#include "Test.h"
#include "AudioEasyAccess.h"

void test(){
	AudioManager* am = AudioManager::getInstance();

	//Adding music to filename's map
	am->add("1", "FileName1.mp3");
	am->add("2", "FileName2.mp3");

	char c = 0;

	//Testing based on user input
	while (42){
		c = _getch();
		cout << (int)c << endl;
		switch (c){
		case 'c':
		case 'C':
			delete am;
			AudioRenderer::destroy();
			return;
		case 'p':
		case 'P':
			(AudioRenderer::Instance())->pauseMusic();
			break;
		case 's':
		case 'S':
			(AudioRenderer::Instance())->stopMusic();
			break;
		case '1':
			(AudioRenderer::Instance())->loadAndPlayMusic("1", am);
			break;
		case '2':
			(AudioRenderer::Instance())->loadAndPlayMusic("2", am);
			break;
		case 'u':
		case 'U':
			(AudioRenderer::Instance())->musicVolumeUp();
			break;
		case 'd':
		case 'D':
			(AudioRenderer::Instance())->musicVolumeDown();
			break;
		case 'm':
		case 'M':
			(AudioRenderer::Instance())->muteMusic();
			break;
		case 'r':
		case 'R':
			(AudioRenderer::Instance())->musicVolumeReset();
			break;
		default:
			break;
		}
	}
}


void TDtest(){
	AudioEasyAccess* aea = AudioEasyAccess::getInstance();

	aea->playMusic("a", "drumloop.wav");
	aea->playSFX("b", "drumloop.wav");
	SoundSource* s = aea->getSoundSource("c", "jaguar.wav", -1.0, 0.0, 0.0);
	s->playSound();
}