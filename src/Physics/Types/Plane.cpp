#include "Plane.h"

Plane fPlane::Create(Vec3 position, float size, ENGINE_AXIS axis)
{
	Plane p;

	p.position  = position;
	p.normal    = { 0, 0, 0 };
		
	switch (axis)
	{
		case ENGINE_AXIS::X:  { p.normal = { 0, 0, 1 }; } break;
		case ENGINE_AXIS::Y:  { p.normal = { 0, 0, 1 }; } break;
		case ENGINE_AXIS::Z:  { p.normal = { 0, 1, 0 }; } break;
		case ENGINE_AXIS::XY: { p.normal = { 0, 0, 1 }; } break;
		case ENGINE_AXIS::XZ: { p.normal = { 0, 1, 0 }; } break;
		case ENGINE_AXIS::YZ: { p.normal = { 0, 1, 0 }; } break;
	}			

	return p;
}

POS_IN_REF_TO_PLANE fPlane::PointPositionInReferenceToPlane(Vec3 &planePosition, Vec3 &planeNormal, Vec3 &position)
{
	float d = planePosition * planeNormal * -1;
	float f = planeNormal   * position + d;

	if		(f > 0)	{ return { ABOVE_THE_PLANE, f }; }
	else if (f < 0) { return { BELOW_THE_PLANE, f }; }

	return { ON_THE_PLANE, f };
}

POS_IN_REF_TO_PLANE fPlane::PointPositionInReferenceToPlane(Plane &p, Vec3 &position)
{
	float d = p.position * p.normal * -1;
	float f = p.normal * position + d;

	if		(f > 0) { return { ABOVE_THE_PLANE, f }; }
	else if (f < 0) { return { BELOW_THE_PLANE, f }; }

	return { ON_THE_PLANE, f }; 
}


//					      | v  *  n     |
// Projected Vector = v - | ------- * n |
//						  | |n|*|n|     |
Vec3 fPlane::ProjectVectorOntoPlane(Vec3 &v, Plane &p)
{
	float mag = Magnitude(p.normal);
	Vec3 projectionOnToNormal = ((v * p.normal) / (mag * mag)) * p.normal;

	return v - projectionOnToNormal;
}

//					      | v  *  n     |
// Projected Vector = v - | ------- * n |
//						  | |n|*|n|     |

Vec3 fPlane::ProjectVectorOntoPlane(Vec3 &v, Vec3 &planeNormal)
{
	float mag = Magnitude(planeNormal);
	Vec3 projectionOnToNormal = ((v * planeNormal) / (mag * mag)) * planeNormal;

	return v - projectionOnToNormal;
}
