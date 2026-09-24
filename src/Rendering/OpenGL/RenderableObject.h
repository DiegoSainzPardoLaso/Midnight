#pragma once

#include "Material_OGL.h"

#include "OGLUtilities.hpp"

#include "../Material.h"
#include "../../Types/Mesh.h"
#include "../../Engine/EngineConfig.h"


struct StaticRendereableObjectOpenGL
{	
	Material_OGL material;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};

struct AnimatedRendereableObjectOpenGL
{
	ENGINE_TYPE   objectType;

	AnimatedMesh *mesh;
	Material_OGL  material;

	unsigned int  VAO;
	unsigned int  VBO;
	unsigned int  EBO;
};


namespace fRenderableObject
{	
	StaticRendereableObjectOpenGL   Create(StaticMesh &mesh, Material &material);
	AnimatedRendereableObjectOpenGL Create(ENGINE_TYPE type, AnimatedMesh &mesh, Material &material);
}


