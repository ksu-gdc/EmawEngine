#include "stdafx.h"
#include "Font.h"

Font::Font()
{
	FontFace = "";

}


Font::~Font()
{
}

// ---------------------------------------------------------------------
// Adds a new character to the font.
// ---------------------------------------------------------------------
// fontChar:	Pointer to FontChar object to add. 
// ---------------------------------------------------------------------
// returns:		nothing.
// ---------------------------------------------------------------------
void Font::addChar(FontChar* fontChar){

	fontCharacters.insert(std::pair<int, FontChar*>(fontChar->id, fontChar));

}