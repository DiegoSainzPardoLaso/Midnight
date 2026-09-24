#include "Quaternion.h"

Quat::Quat(float x, float y, float z, float w)
{
	// @note This constructor, is used for when the quaternions are already calculated, and I just want to store them
	// It's useful for loading MOF and MAF files, as the rotations are already calculated when exporting from Maya
	//
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quat operator +  (Quat  q, Quat o) { return { q.x + o.x, q.y + o.y, q.z + o.z, q.w + o.w };	}
Quat operator -  (Quat  q, Quat o) { return { q.x - o.x, q.y - o.y, q.z - o.z, q.w - o.w };	}
Quat operator *  (Quat  q, Quat o)
{
	return
	{
		(q.w * o.x) + (q.x * o.w) + (q.y * o.z) - (q.z * o.y), 
		(q.w * o.y) - (q.x * o.z) + (q.y * o.w) + (q.z * o.x),
		(q.w * o.z) + (q.x * o.y) - (q.y * o.x) + (q.z * o.w),
		(q.w * o.w) - (q.x * o.x) - (q.y * o.y) - (q.z * o.z)
	};
}
Quat operator *  (Quat  q, float scalar) { return { q.x * scalar, q.y * scalar, q.z * scalar, q.w * scalar }; }
Quat operator /  (Quat  q, float scalar) { return { q.x / scalar, q.y / scalar, q.z / scalar, q.w / scalar }; }
bool operator == (const Quat &q, Quat o) { return fabs(q.x - o.x) <= 1e-06 && fabs(q.y - o.y) <= 1e-06 && fabs(q.z - o.z) <= 1e-06 && fabs(q.w - o.w) <= 1e-06; }
bool operator != (const Quat &q, Quat o) { return fabs(q.x - o.x)  > 1e-06 || fabs(q.y - o.y)  > 1e-06 || fabs(q.z - o.z)  > 1e-06 || fabs(q.w - o.w)  > 1e-06; }



Quat CreateQuaternionFromAxisAndAngle(float degreesAngle, float xAxis, float yAxis, float zAxis)
{
	Quat q;
	degreesAngle = degreesAngle * PI / 180.0f;

	q.w = cos(degreesAngle / 2);

	q.x = xAxis * sin(degreesAngle / 2);
	q.y = yAxis * sin(degreesAngle / 2);
	q.z = zAxis * sin(degreesAngle / 2);

	return q;
}

Quat EulerToQuaternion(float xAngle, float yAngle, float zAngle)
{	
	float roll  = xAngle * PI / 180.0f;
	float pitch = yAngle * PI / 180.0f;
	float yaw   = zAngle * PI / 180.0f;

	float c1	= cos(pitch / 2);
	float c2	= cos(yaw / 2);
	float c3	= cos(roll / 2);

	float s1	= sin(pitch / 2);
	float s2	= sin(yaw / 2);
	float s3	= sin(roll / 2);

	float w		= c1 * c2 * c3 - s1 * s2 * s3;
	float x		= s1 * s2 * c3 + c1 * c2 * s3;
	float y		= s1 * c2 * c3 + c1 * s2 * s3;
	float z		= c1 * s2 * c3 - s1 * c2 * s3;

	return Quat(x, y, z, w);
}

Quat  Conjugate(Quat& q)
{
	return { q.w, -q.x, -q.y, -q.z };
}

float Magnitude(Quat& q)
{
	return (float)(sqrt((q.w * q.w) + (q.x * q.x) + (q.y * q.y) + (q.z * q.z)));
}

Quat  Inverse(Quat& q)
{
	float mag = Magnitude(q);
	return Conjugate(q) / (mag * mag);
}

Quat  Normalize(Quat& q)
{
	return q / Magnitude(q);
}

Quat  Lerp(Quat& q0, Quat& q1, float a)
{
	Quat fQ = q0 * (1.0f - a) + q1 * a;
	return fQ / Magnitude(fQ);
}


