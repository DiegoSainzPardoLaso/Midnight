#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "../File/File.h"

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Math/Quaternion.h"
#include "../Math/LinearAlgebra.h"

#include "../Types/Mesh.h"
#include "../Physics/Types/AABB.h"	
#include "../Utilities/Utilities.hpp"
#include "../Animation/Types/Joint.h"
#include "../Animation/Types/Skeleton.h"

#include "../Utilities/Message/MessageUtils.h"


namespace MOFLoader
{
	#define __MOF__   ".mof"
	#define __MOFT__  ".moft"

	struct Data
	{		
		StaticMesh   staticMesh;

		AnimatedMesh mesh;
		Skeleton     skeleton;

		AABB  boundingBox;		
		bool  successReading;
	};

	// @note If the mesh isn't animated I just skip the skeleton part and done
	//
	Data LoadMesh(const char* path); 

	namespace Internal
	{
		Data LoadBinary(const char* path);
		Data LoadASCII(const char* path);
	}
}