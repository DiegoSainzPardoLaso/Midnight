#pragma once

#include "../Geometry/DebugShapes.h"

#include "../Rendering/OpenGL/Material_OGL.h"

struct Grid
{		
	float size;
	float units;
	
	Material_OGL material;		
};

namespace fGrid
{
	Grid* Initialize();
	void  Update(Grid*& grid);

	namespace Helpers
	{
		void SetGridSize(Grid *&grid, float size);
		void SetGridUnits(Grid *&grid, float units);
	}
}

