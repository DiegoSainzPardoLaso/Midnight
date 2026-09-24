#include "Physics.h"

bool fPhysics::Intersects(const Ray &r, const Plane &p, Vec3 &intersection)
{
	// ray origin	                        = p0 
	// Intersection                         = P0 + t * dir	
	// Plane normal                         = [ a, b, c ]
	// Plane Equation                       = ax + by + cz + d = 0
	// Distance from [0, 0, 0] to the plane = d
	// 
	// Substituting the intersection point inside the plane equation ->
	// 
	// a(p0.x + dir.x * t) + b(p0.y + dir.y * t) + c(p0.z + dir.z * t) + d = 0	
	//
	// Clear t
	// 
	// t = -(a * p0.x + b * p0.y + c * p0.z + d)
	//	   -------------------------------------
	//		 a * dir.x + b * dir.y + c * dir.z
	// 
	// Knowing that a, b, c         = plane's normal
	// That p0.x, p0.y, p0.z        = ray's origin
	// And that dir.x, dir.y, dir.z = ray's direction
	// The equation can be rewriten as:
	// 
	// t = -( n * p0 + d)
	//     --------------
	//		   n * dir
	// 
	// And now knowing 't' I can calculate the intersection point using the 
	// parametric line equation	
	// 
	// Q = P0 + t * dir;
	//
	Vec3  planePosition = p.position;	

	Vec3  n   = p.normal;
	Vec3  p0  = r.p0;
	Vec3  dir = r.dir;								 // Normalization is undesired here
	float d   = planePosition * n * -1;

	float orthogonal  = Dot(dir, n);
	float insidePlane = n * p0 + d;

	if (std::abs(orthogonal)  <= 1e-4) { return false; }	 // Check if the line is orthogonal to the plane
	if (std::abs(insidePlane) <= 1e-4) { return false; }
	

	float t      = (-((n * p0) + d)) / (n * dir);	
	intersection = p0 + t * dir;

	return true;
}

// Cyrus Beck Algorithm - Line Clipping
bool fPhysics::Intersects(const Ray &r, const AABB &aabb, Vec3 &intersection)
{
	Vec3 d = Normalize(r.dir);
	
	if (d.x == 0 || d.y == 0 || d.z == 0) { return false; }

	float tminX = ((aabb.min.x + aabb.position.x) - r.p0.x) / d.x;
	float tmaxX = ((aabb.max.x + aabb.position.x) - r.p0.x) / d.x;	
	float tminY = ((aabb.min.y + aabb.position.y) - r.p0.y) / d.y;
	float tmaxY = ((aabb.max.y + aabb.position.y) - r.p0.y) / d.y;	
	float tmaxZ = ((aabb.max.z + aabb.position.z) - r.p0.z) / d.z;
	float tminZ = ((aabb.min.z + aabb.position.z) - r.p0.z) / d.z;


	float tmin = fmaxf(fmaxf(fminf(tminX, tmaxX), fminf(tminY, tmaxY)), fminf(tminZ, tmaxZ));
	float tmax = fminf(fminf(fmaxf(tminX, tmaxX), fmaxf(tminY, tmaxY)), fmaxf(tminZ, tmaxZ));
	
	// The intersection is happening behind the ray's origin
	if (tmax < 0) { return false; }

	intersection = r.p0 + d * tmin;

	return tmin < tmax;	
}