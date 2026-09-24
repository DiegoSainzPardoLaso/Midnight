#pragma once

#include <cmath>
#include "../MathConstants.h"

struct Vec3
{
	float x;
	float y;
	float z;
};

Vec3 operator  + (const Vec3 &a, const Vec3 &b);
Vec3 operator  + (const Vec3 &a, float s);
Vec3 operator  + (float s, const Vec3 &a);

Vec3 operator  - (const Vec3 &a, const Vec3 &b);
Vec3 operator  - (const Vec3 &a, const float s);

float operator * (const Vec3 &a, const Vec3 &b);
Vec3  operator * (const Vec3 &a, const float s);
Vec3  operator * (float s, const Vec3 &a);

Vec3 operator  / (const Vec3 &a, const float s);

void operator += (Vec3 &a, const Vec3 &b);
void operator -= (Vec3 &a, const Vec3 &b);
void operator += (Vec3 &a, const float s);
void operator -= (Vec3 &a, const float s);
void operator *= (Vec3 &a, float s);
void operator /= (Vec3 &a, float s);

bool operator == (const Vec3 &a, const Vec3 &b);
bool operator != (const Vec3 &a, const Vec3 &b);

float Magnitude      (Vec3 &v);
Vec3  Normalize      (Vec3  v);
float SquaredLength  (Vec3 &v);
float Dot            (Vec3 &v0, Vec3 &v1);
Vec3  Cross          (Vec3 &v0, Vec3 &v1);
Vec3  Lerp           (Vec3 &v0, Vec3 &v1, float a);
Vec3  Slerp          (Vec3 &v0, Vec3 &v1, float a);
float Angle		     (Vec3 &v0, Vec3 &v1);
float SignedAngle    (Vec3 &v0, Vec3 &v1, Vec3 &referenceAxis);
float SignedAngleYolo(Vec3 &v0, Vec3 &v1);