#pragma once

#include <map>
#include <string>
#include "FontChar.h"

class Font{
private:
	std::map<int, FontChar*> fontCharacters;
public:
	Font();
	~Font();
	std::string FontFace;

	void addChar(FontChar*);

};