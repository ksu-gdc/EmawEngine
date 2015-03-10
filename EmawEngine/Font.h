#pragma once

#include "stdafx.h"
#include <map>
#include <string>
#include "FontChar.h"

class Font :
	public Asset
{
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

	void* load(char*);
	void* load(std::string);
	void* getData();
	bool unload(void);
	std::pair<int, int>* Font::textSize(std::string);
	std::string Font::createTextBlock(std::string, int);
	Model* Font::createFontModel(std::string, float, float, float, float*, float);
	
};