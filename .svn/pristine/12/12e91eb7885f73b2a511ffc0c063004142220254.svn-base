#pragma once

#include "../../Types/Mesh.h"
#include "../../Rendering/OpenGL/Material_OGL.h"

#include "../../Rendering/OpenGL/OGLUtilities.hpp"

#include "../../Math/Vector.h"

struct AABB
{
	Vec3 position;
	Vec3 min;
	Vec3 max;	

	DebugMesh	 mesh;
	Material_OGL material;
};

namespace fAABB
{
	AABB Create(Vec3 minCooridnates, Vec3 maxCoordinates, Vec3 color);
	Vec3 CalculateCentroid(AABB &aabb);
}