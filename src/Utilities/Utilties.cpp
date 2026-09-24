#include "Utilities.hpp"

Vec2 fUtil::PixelsToNormalizeDeviceCoords(float x, float y, float screenWidth, float screenHeight, bool invertY)
{
	x = (x / screenWidth) * 2 - 1;
	invertY ? y = 1 - (y / screenHeight * 2) : y = (y / screenHeight) * 2 - 1;

	return { x, y };
}

std::vector<std::string> fUtil::TokenizeLine(std::string& line, const char regex, const char secondRegex, const char thirdRegex)
{
	std::vector<std::string> tokenVector;
	size_t tokenStartingIndex = 0;
	size_t tokenLength        = 0;

	for (size_t currentIndex = 0; currentIndex < line.size(); currentIndex++)
	{
		if ((line[currentIndex] == regex && regex != NULL) || (line[currentIndex] == secondRegex && secondRegex != NULL) || (line[currentIndex] == thirdRegex && thirdRegex != NULL))
		{
			tokenLength        = currentIndex - tokenStartingIndex;
			std::string token  = line.substr(tokenStartingIndex, tokenLength);
			if (token.compare("")) { tokenVector.push_back(token); }
			tokenStartingIndex = currentIndex + 1;
		}
	}

	// Used to get the last token as the format doesn't include any indicator at the end of the line
	//
	tokenVector.push_back(line.substr(tokenStartingIndex, line.size()));

	return tokenVector;
}

int fUtil::GetSequenceOfCharactersLength(const char* data)
{
	int size = 0;
	while (*data++ != '\0') { size++; }
	return size;
}

int fUtil::GetSequenceOfCharactersLengthNoSpacing(const char* data)
{
	int size = 0;
	while (*data != '\0')
	{
		if (*data++ != ' ') 
		{
			size++; 
		}
	}

	return size;
}

bool fUtil::IsThisSequenceOfCharactersInsideTheString(std::string& line, std::string sequence)
{
	std::string  currentSequence = "";
	unsigned int sqcIdx          = 0;

	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] == sequence[sqcIdx])
		{
			currentSequence += line[i];
			sqcIdx++;
		}
		else
		{
			currentSequence = "";
			sqcIdx          = 0;
		}

		if (!currentSequence.compare(sequence)) 
		{
			// std::cout << currentSequence << '\n';
			return true; 
		}
	}

	return false;
}

bool fUtil::CompareCharArrayWithStringLiteral(const char* c, const char* l)
{
	while (*l != '\0')
	{
		if (*l++ != *c++) { return false; }
	}

	return true; 
}

const char* fUtil::RemoveCharactersFromString(char* str, int uniformCount, ...)
{
	char* retStr;
	char* regex = reinterpret_cast<char*>(malloc(uniformCount));
	std::string cleanString = "";
	
	va_list list;
	va_start(list, uniformCount);
	for (int i = 0; i < uniformCount; i++) { regex[i] = va_arg(list, char); }
	va_end(list);

	int strLength = fUtil::GetSequenceOfCharactersLength(str);

	for (int i = 0; i < strLength; i++)
	{
		bool include = true;
		for (int r = 0; r < uniformCount; r++)
		{
			if (regex[r] == str[i]) 
			{
				include = false; 
				break;
			}
		}

		if (include) { cleanString += str[i]; }		
	}

	free(regex);
	retStr = reinterpret_cast<char*>(malloc(cleanString.size()));
	strcpy(retStr, cleanString.data());
		
	return retStr;
}