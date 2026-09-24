#include "Font.h"

// @note Use an unordered map wich uses a hash table (O(1)) instead of a map which uses a binary tree (O(log(n))
//
Font fFont::Load(const char* fntPath, const char* textureAtlasPath, const char* shaderPath)
{			
	// Retrieve all font information
	//
	bool	  readingKernings         = false;
	int		  characterCount          = 0;
	int		  numberOfCharactersRead  = 0;
	Font      font{};
	
	std::ifstream file(fntPath, std::ios::in);
	std::string   line;

	// The .fnt will always follow this pattern
	// char id=32   x=2038  y=0     width=1    height=1     xoffset=0     yoffset=0     xadvance=118   page=0  chnl=15
	//  0   1   2   3   4   5   6    7    8     9     10     11    12       13   14        15    16    17   18  19  20
	//
 	while (std::getline(file, line))
	{
		std::vector<std::string> tokens = fUtil::TokenizeLine(line, ' ', '=', NULL);

		if (numberOfCharactersRead < characterCount)
		{
			Character character{};	
			character.idAscii  = std::stoi(tokens[2]);
			character.U0       = std::stoi(tokens[4]);
			character.V0       = std::stoi(tokens[6]);
			character.width    = std::stoi(tokens[8]);
			character.height   = std::stoi(tokens[10]);
			character.xOffset  = std::stoi(tokens[12]);
			character.yOffset  = std::stoi(tokens[14]);
			character.xAdvance = std::stoi(tokens[16]);
			character.U1	   = character.U0 + character.width;
			character.V1	   = character.V0 + character.height;
			font.characters.emplace(character.idAscii, character);
			
			numberOfCharactersRead++;
		}

		// kerning first=122 second=113 amount=-2  
		//      0    1    2    3    4     5    6
		//
		if (readingKernings)
		{
			int asciiID        = std::stoi(tokens[2]);
			Character& refChar = font.characters.at(asciiID);
			refChar.kernings.emplace((short)std::stoi(tokens[4]), std::stof(tokens[6]));
		}

		if (!tokens[1].compare("face"))								         { font.name       = fUtil::RemoveCharactersFromString(tokens[2].data(), 2, '\\', '"'); }
		if (!tokens[1].compare("lineHeight"))								 { font.lineHeight = std::stoi(tokens[2]);										       }
		if (tokens.size() > 3 && !tokens[3].compare("base"))		         { font.base       = std::stoi(tokens[4]);										       }
		if (!tokens[0].compare("chars")      && !tokens[1].compare("count")) { characterCount  = std::stoi(tokens[2]);										       }
		if (!tokens[0].compare("kernings")   && !tokens[1].compare("count")) { readingKernings = true;														       }
	} 	
		
	font.material = fMaterial_OGL::Create(shaderPath, textureAtlasPath);
	
	return font;
}

// FIXME:
//
void fFont::SetSize(Font& font, float size)
{
	float newSize	 = size / 250;
	font.base		*= newSize;
	font.lineHeight *= newSize;

	for (auto it = font.characters.begin(); it != font.characters.end(); it++)
	{
		Character& character = font.characters.at(it->first);		
		character.width	    *= newSize;
		character.height	*= newSize;
		character.xOffset   *= newSize;
		character.yOffset   *= newSize;
		character.xAdvance  *= newSize;

		for (auto it = character.kernings.begin(); it != character.kernings.end(); it++)
		{			
			float& amount = it->second;
			amount	     *= newSize;
		}
	}
}