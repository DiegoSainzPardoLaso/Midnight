#pragma once

#include <unordered_map>

// <param name="IDASCII:">	Character ascii identifier													</param>
// <param name="XU:">		Coordinate inside the atlas texture											</param>
// <param name="YV:">		Coordinate inside the atlas texture											</param>
// <param name="WIDTH:">	Character width relative to the X position									</param>
// <param name="HEIGHT:">	Character height relative to the Y position									</param>
// <param name="XOFFSET:">	Next character top left vertex X offset										</param>
// <param name="YOFFSET:">	Next character top left vertex Y offset										</param>
// <param name="XADVANCE:">	Virtual cursor x offset after each character								</param>
// <param name="KERNINGS:"> Map of amounts that will use kerning correction when combined with this one </param>
struct alignas(8) Character
{
	uint16_t idAscii;
		  
	uint16_t U0;
	uint16_t V0;
		  
	uint16_t U1;
	uint16_t V1;
		  
	float width;
	float height;
		  
	float xOffset;
	float yOffset;
	float xAdvance;

	std::map<short, float> kernings;
};