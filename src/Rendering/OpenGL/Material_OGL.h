#pragma once

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "../../Utilities/Definitions.h"

struct Material_OGL
{
    Shader   shader;
    Texture *textures;
    uint8_t  textureCount; // OpenGL allows for 80 textures for each shader program 0 - 79

    // Parameters
    // Roughness
    // Metalness
    // Specular
};

namespace fMaterial_OGL
{
    Material_OGL Create(const char *shaderSrc);
    Material_OGL Create(const char *shaderSrc, const char *texturePath);
    Material_OGL Create(const char* shaderSrc, std::vector<const char*>& textures);
}
