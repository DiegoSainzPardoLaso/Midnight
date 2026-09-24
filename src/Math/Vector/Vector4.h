#pragma once

struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
	Vec4() : x(1), y(1), z(1), w(1) {};

	Vec4 operator + (Vec4& other)  { return{ x + other.x, y + other.y, z + other.z, w + other.w }; }
	Vec4 operator - (Vec4& other)  { return{ x - other.x, y - other.y, z - other.z, w - other.w }; }
	Vec4 operator * (float scalar) { return{ x * scalar, y * scalar, z * scalar, w * scalar }; }
	Vec4 operator / (float scalar) { return{ x / scalar, y / scalar, z / scalar, w / scalar }; }

	float operator * (Vec4 other) { return (x * other.x + y * other.y + z * other.z + w * other.w); }

};