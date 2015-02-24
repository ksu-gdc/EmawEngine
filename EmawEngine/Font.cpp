#include "stdafx.h"
#include <fstream>
#include <string>
#include "Font.h"

using namespace std;

Font::Font()
{
	loadingFontChar = NULL;
}


Font::~Font()
{
}

void Font::loadFont(string fontPath){

	try{

		ifstream fontInputStream;
		fontInputStream.open(fontPath);

		while (fontInputStream){

			string line;
			fontInputStream >> line;
			ParseFontFile(line);
		}
	}
	catch (exception e){
		OutputDebugString(L"Error loading font asset.");
	}

}

void Font::ParseFontFile(string line){

	if (line.find("face=") != std::string::npos){
		int equalIndex = line.find("=");
		fontFace = line.substr(equalIndex + 1, line.length() - 1);
	}
	else if (line.find("count=") != std::string::npos){
		int equalIndex = line.find("=");
		numOfChars = stoi(line.substr(equalIndex + 1, line.length() - 1));
	}
	else if (line.find("file=") != std::string::npos){
		int equalIndex = line.find("=");
		pngPath = line.substr(equalIndex + 1, line.length() - 1);
	}
	else if (line.find("char") != std::string::npos){
		loadingFontChar = new FontChar();
	}
	else if (line.find("id=") != std::string::npos){
		int equalIndex = line.find("=");
		loadingFontChar->id = stoi(line.substr(equalIndex + 1, line.length() - 1));
	}
	else if (line.find("x=") != std::string::npos){
		int equalIndex = line.find("=");
		loadingFontChar->x = stoi(line.substr(equalIndex + 1, line.length() - 1));
	}
	else if (line.find("y=") != std::string::npos){
		int equalIndex = line.find("=");
		loadingFontChar->y = stoi(line.substr(equalIndex + 1, line.length() - 1));
	}
	else if (line.find("width=") != std::string::npos){
		int equalIndex = line.find("=");
		loadingFontChar->width = stoi(line.substr(equalIndex + 1, line.length() - 1));
	}
	else if (line.find("height=") != std::string::npos){
		int equalIndex = line.find("=");
		loadingFontChar->height = stoi(line.substr(equalIndex + 1, line.length() - 1));
	}
	else if (line.find("xoffset=") != std::string::npos){
		int equalIndex = line.find("=");
		loadingFontChar->xoffset = stoi(line.substr(equalIndex + 1, line.length() - 1));
	}
	else if (line.find("yoffset=") != std::string::npos){
		int equalIndex = line.find("=");
		loadingFontChar->yoffset = stoi(line.substr(equalIndex + 1, line.length() - 1));
		fontCharacters.insert(pair<int, FontChar*>(loadingFontChar->id, loadingFontChar));
		loadingFontChar = NULL;
	}
}
