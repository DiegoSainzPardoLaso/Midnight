#pragma once

#include <vector>
#include <fstream>
#include <map>

#include "Character.h"
#include "../../Rendering/OpenGL/Material_OGL.h"
#include "../../Utilities/Utilities.hpp"

struct Font
{
    const char* name;
    std::map<int, Character> characters;
    Material_OGL			     material;

    float					 size;
    float					 lineHeight;
    float					 base;

};


namespace fFont
{
    Font Load(const char* path, const char* textureAtlasPath, const char* shaderPath);
    void SetSize(Font& font, float size);
}


