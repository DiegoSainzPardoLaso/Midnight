#pragma once

#include "../Types/Vertex.h"
#include "../Types/Mesh.h"
#include "../Math/Vector/Vector3.h"

namespace fGeometry
{
	GUI_Mesh_Quad CreateScreenSpaceQuadHeapFree(float x, float y, float width, float height, Vec3 color);
	GUIMesh     CreateScreenSpaceQuad(float x, float y, float width, float height, Vec3 color);
	GUIMesh     CreateScreenSpaceQuad(float x, float y, float width, float height, float U0, float V0, float U1, float V1);
}