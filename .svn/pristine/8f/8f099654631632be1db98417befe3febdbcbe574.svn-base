#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"
#include "MathConstants.h"

// Midnight Linear Algebra AKA 'MILA'
//
namespace MILA
{	
	Mat4  BuildModelSpaceTransform(Vec3& position, Quat& orientation, Vec3& scale); // @note Delete
	Vec3  GetDirectionFromQuaternion(Quat &q);
	Vec3  RotateVectorByQuaternion(Vec3 &v, Quat &orientation);
	
	float DegToRad(float d);
	float RadToDeg(float r);
}