#pragma once

#include <cmath>
#include "MathConstants.h"


struct Quat
{
	float x; 
	float y; 
	float z; 
	float w; 
	
	Quat() : x(0), y(0), z(0), w(0) {};
	Quat(float x, float y, float z, float w);
};

// @note not the most optimal thing passing this ones as copies...
Quat operator +  (Quat q, Quat o);
Quat operator -  (Quat q, Quat o);
Quat operator *  (Quat q, Quat o);
Quat operator *  (Quat q, float scalar);
Quat operator /  (Quat q, float scalar);
bool operator != (const Quat &q, Quat o);
bool operator == (const Quat &q, Quat o);

Quat CreateQuaternionFromAxisAndAngle(float degreesAngle, float xAxis, float yAxis, float zAxis);
Quat EulerToQuaternion(float xAngle, float yAngle, float zAngle);

float Magnitude(Quat& q);
Quat  Conjugate(Quat& q);
Quat  Inverse  (Quat& q);
Quat  Normalize(Quat& q);
Quat  Lerp(Quat& q0, Quat& q1, float a);