#include "Material.h"

Material fMaterial::Create(const char *shaderPath)
{
	Material m;

	strcpy(m.shaderPath, shaderPath);


	return m;
}