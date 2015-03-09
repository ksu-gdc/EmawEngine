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

// ---------------------------------------------------------------------
// Loads a font asset by reading in a font file.
// ---------------------------------------------------------------------
// fontPath:	The path to the font file.
// ---------------------------------------------------------------------
// returns:		none.
// ---------------------------------------------------------------------
void Font::loadFont(string fontPath){

	try{

		ifstream fontInputStream;
		fontInputStream.open(fontPath);

		// Iterate through each line of the font file,
		// parsing the lines until the all the necessary
		// details of the font have been read and stored.
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

// ---------------------------------------------------------------------
// Parses the font file, extracting all the information needed.
// ---------------------------------------------------------------------
// line:		The line to parse.
// ---------------------------------------------------------------------
// returns:		none.
// ---------------------------------------------------------------------
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
	else if (line.find("lineHeight=") != std::string::npos){
		int equalIndex = line.find("=");
		lineHeight = stoi(line.substr(equalIndex + 1, line.length() - 1));
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

// ---------------------------------------------------------------------
// Calculates the height and maximum width of a block of text.
// ---------------------------------------------------------------------
// text:		The text to calculate the height and max width of.
// ---------------------------------------------------------------------
// returns:		Returns a pair of ints <maximum width, height>.
// ---------------------------------------------------------------------
pair<int, int>* Font::textSize(string text){

	int curWidth = 0;
	int maxWidth = 0;
	int line = 0;

	for(char& c : text){

		// If the first character exists, then we have atleast 1 line.
		if (line == 0){
			line = 1;
		}

		// If a new line character is found, then we are on a new line.
		if (c == '\n'){
			
			line++;

			// If the width of the current line is bigger than the max
			// width, then set the max width to the current lines width.
			if (curWidth > maxWidth){
				maxWidth = curWidth;
			}

			curWidth = 0;
		}
		else{

			// If a character does not exist then the string size cannot be calculated.
			if (fontCharacters.count(c) != 1){
				return new pair<int, int>(-1, -1);
			}

			// Add the character's width to the current width.
			curWidth += fontCharacters.at(c)->width;

		}
	}

	return new pair<int, int>(maxWidth, line * lineHeight);

}

// ---------------------------------------------------------------------
// Creates a text block of a certain width.
// ---------------------------------------------------------------------
// text:		The text to turn into a block.
// width:		The width the block needs to be.
// ---------------------------------------------------------------------
// returns:		Returns a string with new lines placed so that the
//				the block of text is of the proper width.
// ---------------------------------------------------------------------
string Font::createTextBlock(string text, int width){
	
	// Index pointing to the first letter of a word.
	string::size_type firstLetterIndex = 0;

	string newTextBlock;
	int curWidthAvailable = width;
	int wordWidth = 0;
	string curWord;

	for (string::size_type i = 0; i < text.size(); ++i){

		if (text[i] == ' '){
				
			if (curWidthAvailable - wordWidth >= 0){
				newTextBlock.append(curWord + " ");
				curWidthAvailable -= (wordWidth + fontCharacters.at(text[i])->width);
				curWord = "";
				wordWidth = 0;
			}
			else{
				newTextBlock.append("\n");
				curWidthAvailable = width;
				curWord.append(" ");
			}
		}
		else if (text[i] == '\n'){
			newTextBlock.append("\n");
			curWidthAvailable = width;
		}
		else{

			// If a character does not exist then the string size cannot be calculated.
			if (fontCharacters.count(text[i]) != 1){
				return "Error: Bad character in text";
			}

			string s(1, text[i]);
			curWord.append(s);
			wordWidth += fontCharacters.at(text[i])->width;
		}

		if (i == text.size() - 1){

			if (curWidthAvailable - wordWidth >= 0){
				newTextBlock.append(curWord + " ");
			}
			else{
				newTextBlock.append("\n");
				newTextBlock.append(curWord + " ");
			}
		}
	}

	return newTextBlock;

}
