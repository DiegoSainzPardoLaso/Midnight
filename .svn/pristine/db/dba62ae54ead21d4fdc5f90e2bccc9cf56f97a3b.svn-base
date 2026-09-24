// ========================================================================================================================
// Notes
// ========================================================================================================================
// 
// @note When reading, the parent of a bone will always be before the bone.
// So when retrieving the parent index, I can just look for it inside the skeleton and It will always be there. 
// No need to store an integer telling me where to look at. I can retrieve the parent right when reading the file
//
// ========================================================================================================================
#pragma once

#include <cstdint>

#include "../../Math/Matrix.h"
#include "../../Math/Quaternion.h"
#include "../../Math/Vector/Vector3.h"

struct Joint
{
	char*    name;
		
	uint32_t idx;
	uint32_t childCount;
	Joint*   parent;
	Joint**  children;

	Vec3	 position;
	Quat	 orientation;
	Vec3	 scale;
		
	Mat4     animatedTransform;
	Mat4	 originalTransform;		// The A/T Pose transform, bassically the default joint position/Orientation/scale relative to the root
	Mat4	 skeletonTransform;		// Used to display the real position of the skeleton

	bool operator == (Joint& other) { return idx == other.idx; }
	bool operator != (Joint& other) { return idx != other.idx; }
};

namespace fJoint
{		
	Mat4 CalculateParentSpace(Joint& joint);
	Mat4 CalculateInverseCharacterSpace(Joint& joint, Joint& root);
	Mat4 CalculateCharacterSpace(Joint& joint, Joint& root);
	Mat4 CalculateWorldSpace(Joint& joint);
}