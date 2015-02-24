#pragma once

#include "stdafx.h"
#include <map>
#include <string>
#include "FontChar.h"

class Font{
private:
	std::map<int, FontChar*> fontCharacters;
	void ParseFontFile(std::string line);
	FontChar* loadingFontChar;
	std::string fontFace;
	std::string pngPath;
	int numOfChars;
	int lineHeight;
public:
	Font();
	~Font();

	void loadFont(std::string);
	std::pair<int, int>* Font::textSize(std::string line);
	std::string Font::createTextBlock(std::string text, int width);
	
};