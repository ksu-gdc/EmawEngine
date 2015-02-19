#include "stdafx.h"
#include "FontManager.h"
#include <fstream>
#include <string>

using namespace std;

FontManager::FontManager()
{

}


FontManager::~FontManager()
{
}

void FontManager::loadFont(string fontPath){

	// If the font has already been loaded, return.
	if (fonts_map.find(fontPath) != fonts_map.end()){
		return;
	}

	bool isReadingChars = false;
	
	try{

		ifstream fontInputStream;
		fontInputStream.open(fontPath);

		Font* font = new Font();

		while (fontInputStream){

			std:string line;
			fontInputStream >> line;

			// If the font face has not be found, search newest string for font face.
			if (font->FontFace.empty()){
				font->FontFace = ParseFontFace(line);
			}

			// If the line describes a character in the font, then parse the line and
			// add the new character to the font.
			if (isReadingChars){
				font->addChar(ParseCharLine(line, *font));
			}
			else{
				isReadingChars = hasPassedCharInfoLine(line);
			}
		}
	}
	catch (exception e){
		OutputDebugString(L"Error loading font asset.");
	}

}

// ---------------------------------------------------------------------
// Searches a line read in from the font file to determine if it contains
// the font face or name of the font.
// ---------------------------------------------------------------------
// line:		The line to search for the font face.
// ---------------------------------------------------------------------
// returns:		The name of the font (the font face).
// ---------------------------------------------------------------------
string FontManager::ParseFontFace(string line){

	int faceIndex = 0;

	string fontFace;

	// Read through each character looking for the line face=" indicating next
	// characters contain the name of the font.
	for (char& c : line){

		if (FindFaceIdentifier(c, faceIndex)){

			// If a quote is found, the end of the face name has been found.
			if (c == '\"') break;

			fontFace += c;
		}
	}

	return fontFace;

}

// ---------------------------------------------------------------------
// Determines if the face identifier has been found so that the name of
// the face can begin to be read.
// ---------------------------------------------------------------------
// c:			character to check.
// faceIndex:	index on the char arract face that indexes the face
//				identifier string associated with the font file.
// ---------------------------------------------------------------------
// returns:		True if the identifier has been found. False otherwise.
// ---------------------------------------------------------------------
bool FontManager::FindFaceIdentifier(char c, int &faceIndex){

	// Face identifier.
	// IMPORTANT: If format for font file changes, check this identifier.
	static const char* face = "face=\"";

	// If face identifier has been found, return true.
	if (faceIndex == strlen(face)) return true;

	// Check if character is found in face identifier.
	if (c == face[faceIndex]){
		faceIndex++;
	}
	else{

		// If an f has been found, but face=" was not found,
		// reset index to continue looking for face=".
		if (faceIndex != 0) faceIndex = 0;
	}

	return false;

}

// ---------------------------------------------------------------------
// Determines if the line contains the char identifier indicating that
// the line is describing a font character.
// ---------------------------------------------------------------------
// line:		string to search for char identifier.
// ---------------------------------------------------------------------
// returns:		True if the identifier has been found. False otherwise.
// ---------------------------------------------------------------------
bool FontManager::hasPassedCharInfoLine(string line){

	if (line.compare("char") == 0){
		return true;
	}

	return false;
}

// ---------------------------------------------------------------------
// Parses the char line by all the needed attributes: id, x position,
// y position, width, height, x offset, and y offset.
// ---------------------------------------------------------------------
// line:		String to parse.
// font:		Font to add the character to.
// ---------------------------------------------------------------------
// returns:		Pointer to FontChar to add to the Font.
// ---------------------------------------------------------------------
FontChar* FontManager::ParseCharLine(string line, Font &font){

	FontChar* character = new FontChar();

	character->id = ParseIntAttribute(line, "id=");
	character->x = ParseIntAttribute(line, "x=");
	character->y = ParseIntAttribute(line, "y=");
	character->width = ParseIntAttribute(line, "width=");
	character->height = ParseIntAttribute(line, "height=");
	character->xoffset = ParseIntAttribute(line, "xoffset=");
	character->yoffset = ParseIntAttribute(line, "yoffset=");

	return character;
}

// ---------------------------------------------------------------------
// Parses an attribute identified by the parameter, grabing the value
// of that attribute.
// ---------------------------------------------------------------------
// line:		String to parse.
// identifier:	Identifier of the attribute.
// ---------------------------------------------------------------------
// returns:		Value of the attribute as an int.
// ---------------------------------------------------------------------
int FontManager::ParseIntAttribute(string line, char* identifier){

	int index = 0;
	string integer;

	for (char& c : line){
	
		if (index == strlen(identifier)){
			
			if (c == ' ') break;
			integer += c;
		}

		if (c == identifier[index]){
			index++;
		}
		else{
			if (index != 0) index = 0;
		}
	}

	return stoi(integer);

}