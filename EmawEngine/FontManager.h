#pragma once

#include <map>
#include <string>
#include "stdafx.h"
#include "Font.h"
#include "FontChar.h"

using namespace std;

class FontManager{
private:
	std::map<string, Font*> fonts_map;
public:
	FontManager();
	~FontManager();

	void loadFont(string);
	string ParseFontFace(string);
	bool FindFaceIdentifier(char c, int &faceIndex);
	bool hasPassedCharInfoLine(string line);
	FontChar* ParseCharLine(string line, Font &font);
	int ParseIntAttribute(string line, char* identifier);
};