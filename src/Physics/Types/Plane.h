#pragma once

#include "../../Geometry/DebugShapes.h"
#include "../../Math/Vector.h"
#include "../../Utilities/Definitions.h"


enum SIDE_OF_THE_PLANE
{
	BELOW_THE_PLANE,
	ON_THE_PLANE,
	ABOVE_THE_PLANE,
};

struct POS_IN_REF_TO_PLANE
{
	SIDE_OF_THE_PLANE sideOfThePlane;
	float			  distanceToPlane;
};

struct Plane
{
	Vec3 position;
	Vec3 normal;	
};

namespace fPlane
{
	Plane Create(Vec3 position, float size, ENGINE_AXIS axis);

	POS_IN_REF_TO_PLANE PointPositionInReferenceToPlane(Vec3 &planePosition, Vec3 &planeNormal, Vec3 &position);
	POS_IN_REF_TO_PLANE PointPositionInReferenceToPlane(Plane &p, Vec3 &position);

	Vec3 ProjectVectorOntoPlane(Vec3 &v, Plane &p);
	Vec3 ProjectVectorOntoPlane(Vec3 &v, Vec3 &planeNormal);
}