#pragma once

#include <cmath>

struct Vec2
{	
	union { float x; float width; };
	union { float y; float height; };


};

Vec2  operator +  (const Vec2 &a, const Vec2 &b); 
Vec2  operator -  (const Vec2 &a, const Vec2 &b); 
Vec2  operator *  (const Vec2 &a, float s);
Vec2  operator /  (const Vec2 &a, float s);
float operator *  (const Vec2 &a, const Vec2 &b);

bool  operator == (const Vec2 &a, const	Vec2 &b);
bool  operator != (const Vec2 &a, const Vec2 &b);

Vec2  Lerp(Vec2 &v0, Vec2 &v1, float a);
float Magnitude(Vec2  v);
void  Normalize(Vec2 &v);
float Dot(Vec2 &a, Vec2 &b);