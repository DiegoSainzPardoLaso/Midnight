#include "Vector3.h"


Vec3 operator  + (const Vec3 &a, const Vec3 &b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
Vec3 operator  + (const Vec3 &a, float s)		{ return { a.x + s, a.y + s, a.z + s };		  }
Vec3 operator  + (float s,       const Vec3 &a)	{ return { a.x + s, a.y + s, a.z + s };		  }

Vec3 operator  - (const Vec3 &a, const Vec3 &b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
Vec3 operator  - (const Vec3 &a, const float s)	{ return { a.x - s, a.y - s, a.z - s };		  }

float operator * (const Vec3 &a, const Vec3 &b) { return a.x * b.x + a.y * b.y + a.z * b.z;   }
Vec3  operator * (const Vec3 &a, const float s) { return { a.x * s,  a.y * s,  a.z * s };     }
Vec3  operator * (float s, const Vec3 &a)       { return { a.x * s,  a.y * s,  a.z * s };     }

Vec3 operator  / (const Vec3 &a, const float s) { return { a.x / s,  a.y / s,  a.z / s };     }

void operator += (Vec3 &a, const Vec3 &b)		{ a.x += b.x; a.y += b.y; a.z += b.z;		  }
void operator -= (Vec3 &a, const Vec3 &b)		{ a.x -= b.x; a.y -= b.y; a.z -= b.z;		  }
void operator += (Vec3 &a, float s)		        { a.x += s;   a.y += s;   a.z += s;			  }
void operator -= (Vec3 &a, float s)				{ a.x -= s;   a.y -= s;   a.z -= s;			  }
void operator *= (Vec3 &a, float s)				{ a.x *= s;   a.y *= s;   a.z *= s;			  }
void operator /= (Vec3 &a, float s)				{ a.x /= s;   a.y /= s;   a.z /= s;			  }

bool operator == (const Vec3 &a, const Vec3 &b) { return (fabs(a.x - b.x) <= 1e-06 && fabs(a.y - b.y) <= 1e-06 && fabs(a.z - b.z) <= 1e-06); }
bool operator != (const Vec3 &a, const Vec3 &b) { return (fabs(a.x - b.x) >  1e-06 || fabs(a.y - b.y) >  1e-06 || fabs(a.z - b.z) >  1e-06); }


float Magnitude(Vec3& v)     { return (float)(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z))); }
float SquaredLength(Vec3& v) { return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);                }
float Dot(Vec3& a, Vec3& b)  { return a.x * b.x + a.y * b.y + a.z * b.z;                      }
Vec3  Normalize(Vec3 v)      { return v / Magnitude(v);                                       }

Vec3 Cross(Vec3& v0, Vec3& v1)
{
	return
	{
		(v0.y * v1.z) - (v1.y * v0.z),
	  -((v0.x * v1.z) - (v1.x * v0.z)),
		(v0.x * v1.y) - (v1.x * v0.y)
	};
}

Vec3 Lerp(Vec3& v0, Vec3& v1, float a)
{	
	a  = a > 1 ? 1 : a;
	a *= a >= 0;
	return v0 * (1.0f - a) + v1 * a;
}

// Original formula I was gonna implement
// 
// Q = acos(v0 * v1)
// 
//            |											   |		
// Formula -> |		 sin((1-a) * Q)         sin(a*Q)       |
//			  |	vf = -------------- * v0 + ---------- * v1 |
//			  |		     sin(Q)			      sin(Q)       | 
//			  |											   |			

Vec3 Slerp(Vec3 &v0, Vec3 &v1, float a)
{
	// float dot = v0 * v1;
	// float q = acos(dot);
	// 
	// if (q == 0 || q != q) { q = 0.01f; }
	// 
	// return ((sin((1 - a) * q) / sin(q)) * v0) + ((sin(a * q) / sin(q)) * v1);

	// This version I took from https://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/
	// Dot product - the cosine of the angle between 2 vectors.
	float dot = v0 * v1;
	// Clamp it to be in the range of Acos()
	// This may be unnecessary, but floating point
	// precision can be a fickle mistress.
	dot = dot >  1.0f ?  1 : dot;
	dot = dot < -1.0f ? -1 : dot;
	// Acos(dot) returns the angle between start and end,
	// And multiplying that by percent returns the angle between
	// start and the final result.
	float theta = acos(dot) * a;
	Vec3 RelativeVec = v1 - v0 * dot;
	Normalize(RelativeVec);
	// Orthonormal basis
	// The final result.
	return ((v0 * cos(theta)) + (RelativeVec * sin(theta)));
}

float Angle(Vec3 &v0, Vec3 &v1)
{	
	float n = v0 * v1;
	float d = Magnitude(v0) * Magnitude(v1);

	return acos(n / d) * 180.0f / PI;
}

// Both vectors should belong to the same plane. Otherwhise there would be errors on the returned angle
float SignedAngle(Vec3 &v0, Vec3 &v1, Vec3 &referenceAxis)
{	
	Vec3 rotCrossStart = Normalize(Cross(referenceAxis, v0));
	Vec3 rotCrossEnd   = Normalize(Cross(referenceAxis, v1));
	
	Vec3 startCrossEnd = Normalize(Cross(rotCrossStart, rotCrossEnd));
	int sign		   = referenceAxis * startCrossEnd >= 0 ? 1 : -1;
	float angle		   = Angle(v0, v1) * sign;

	if (angle != angle) { return 0; }	// NAN CHECKING

	return angle;
}

float SignedAngleYolo(Vec3 &v0, Vec3 &v1)
{
	Vec3 cross		   = Cross(v0, v1);
	Vec3 rotCrossStart = Normalize(Cross(cross, v0));
	Vec3 rotCrossEnd   = Normalize(Cross(cross, v1));

	Vec3 startCrossEnd = Normalize(Cross(rotCrossStart, rotCrossEnd));
	int sign		   = cross * startCrossEnd >= 0 ? -1 : 1;
	float angle		   = Angle(v0, v1) *sign;
	
	if (angle != angle) { return 0; }	// NAN CHECKING

	return angle;
}
