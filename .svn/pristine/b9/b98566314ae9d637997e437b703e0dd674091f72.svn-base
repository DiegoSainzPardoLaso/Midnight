#include "Material_OGL.h"

Material_OGL fMaterial_OGL::Create(const char* shaderSrc)
{
	return 
	{
		.shader		  = fShader::Create(shaderSrc),
		.textures	  = nullptr,
		.textureCount = 0,
	};	
}

Material_OGL fMaterial_OGL::Create(const char* shaderSrc, const char* texturePath)
{
	return
	{
		.shader       = fShader::Create(shaderSrc),
		.textures     = fTextureOpenGL::Load(texturePath, false),
		.textureCount = 1,
	};			
}

Material_OGL fMaterial_OGL::Create(const char* shaderSrc, std::vector<const char*>& textures)
{
	return 
	{
		.shader       = fShader::Create(shaderSrc),
		.textures     = fTextureOpenGL::Load(textures, false),
		.textureCount = (uint8_t)textures.size(),
	};
}