#pragma once

#include "../../Math/Matrix.h"
#include "../../Math/Quaternion.h"
#include "../../Math/Vector/Vector3.h"

// @note Each keyframe has an array of transformations, the array is 
// directly related to the joint hierarchy, so transform 0 in a keyframe
// always corresponds to the root joint
//
struct Keyframe
{
	// This are the joints
	// I tought it would be stupid to have the actual joint struct as a list, 'cause
	// I would need to setup the parent son relations and all of that.
	// And like this I can just use the index that the skeleton joints have
	//
	Vec3* position;
	Quat* orientation;
	Vec3* scale;
	Mat4* transform;
	
	int	  jointsCount;
	float timeStamp;
};