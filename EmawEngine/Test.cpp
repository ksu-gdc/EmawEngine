//Testing class for playing music
//Author: Ondrej Kuzela

#include "stdafx.h"
#include "Test.h"

void test(){
	AssetManager* am = new AssetManager();

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
	AssetManager* am = new AssetManager();

	//Adding music to filename's map
	am->add("drum", "drumloop.wav");


	Position* p = new Position(0, 0, 0);
	(AudioRenderer::Instance())->loadAndPlayTDSFX("drum", am, p);
	delete p;

	am->setCharactersActualPosition(0, 0, 0);

	char c = 0;
	Position* pos;

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
		case 'w':
			pos = am->getCharactersActualPosition();
			am->setCharactersActualPosition(pos->getX(), pos->getY() + 1, pos->getZ());
			break;
		case 's':
			pos = am->getCharactersActualPosition();
			am->setCharactersActualPosition(pos->getX(), pos->getY() - 1, pos->getZ());
			break;
		case 'd':
			pos = am->getCharactersActualPosition();
			am->setCharactersActualPosition(pos->getX() + 1, pos->getY(), pos->getZ());
			break;
		case 'a':
			pos = am->getCharactersActualPosition();
			am->setCharactersActualPosition(pos->getX() - 1, pos->getY(), pos->getZ());
			break;
		default:
			break;
		}
	}
}