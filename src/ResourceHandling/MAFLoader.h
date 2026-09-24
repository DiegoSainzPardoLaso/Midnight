#pragma once

#include <fstream>

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Math/Quaternion.h"
#include "../Math/LinearAlgebra.h"

#include "../Animation/Animation.h"
#include "../Animation/Types/Keyframe.h"

#include "../File/File.h"
#include "../Utilities/Utilities.hpp"
#include "../Utilities/Message/MessageUtils.h"

namespace MAFLoader
{
	#define __MAF__   ".maf"
	#define __MAFT__  ".maft"

	Animation LoadAnimation(const char* path);

	namespace Internal
	{
		Animation LoadBinary(const char* path);
		Animation LoadASCII(const char* path);
	}
}