#include "Vector2.h"


Vec2  operator +  (const Vec2 &a, const Vec2 &b) { return { a.x + b.x,  a.y + b.y }; }
Vec2  operator -  (const Vec2 &a, const Vec2 &b) { return { a.x - b.x,  a.y - b.y }; }
Vec2  operator *  (const Vec2 &a, float s)       { return { a.x * s,    a.y * s };   }
Vec2  operator /  (const Vec2 &a, float s)       { return { a.x / s,    a.y / s };   }
float operator *  (const Vec2 &a, const Vec2 &b) { return   a.x * b.x + a.y * b.y;   }
bool  operator == (const Vec2 &a, const Vec2 &b) { return fabs(a.x - b.x) <= 1e-06 && fabs(a.y - b.y) <= 1e-06; }
bool  operator != (const Vec2 &a, const Vec2 &b) { return fabs(a.x - b.x)  > 1e-06 || fabs(a.y - b.y)  > 1e-06; }

Vec2 Lerp(Vec2 &v0, Vec2 &v1, float a)
{
	return v0 * (1 - a) + v1 * a;
}

float Magnitude(Vec2  v)    { return (float)(sqrt((v.x * v.x) + (v.y * v.y))); }
void  Normalize(Vec2 &v)    
{
	float m = Magnitude(v);
	if (m == 0) { return; }
	v = v / Magnitude(v); 
}
float Dot(Vec2 &a, Vec2 &b) { return a.x * b.x + a.y * b.y; }
