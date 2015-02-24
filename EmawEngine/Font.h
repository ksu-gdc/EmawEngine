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
public:
	Font();
	~Font();
	std::string fontFace;
	std::string pngPath;
	int numOfChars;

	void loadFont(std::string);
	
};