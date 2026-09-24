#pragma once

#include <cstdarg>

#include <iostream>
#include <vector>
#include <string>

#include "../Math/Vector.h"
#include "../Math/Matrix.h"

namespace fUtil
{
	Vec2					 PixelsToNormalizeDeviceCoords(float x, float y, float screenWidth, float screenHeight, bool invertY);
	std::vector<std::string> TokenizeLine(std::string &line, const char regex, const char secondRegex, const char thirdRegex);
	int						 GetSequenceOfCharactersLength(const char* data);
	int						 GetSequenceOfCharactersLengthNoSpacing(const char* data);
	bool					 IsThisSequenceOfCharactersInsideTheString(std::string& line, std::string sequence);	
	bool					 CompareCharArrayWithStringLiteral(const char* c, const char* l);
	const char*				 RemoveCharactersFromString(char* str, int uniformCount, ...);	

	template <typename T>
	void CopyArray(T* destiny, T* origin, int size)
	{
		for (size_t i = 0; i < size; i++)
		{
			destiny[i] = *origin++;
		}
	}

	template <typename First, typename Second>
	void CopyArray(First*& destiny, std::vector<Second*>& origin)
	{
		for (size_t i = 0; i < origin.size(); i++)
		{
			destiny[i] = *origin.at(i);
		}
	}
}