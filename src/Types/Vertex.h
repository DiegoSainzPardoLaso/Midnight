#pragma once

#include "../Math/Vector.h"



enum VERTEX_TYPE
{
	STATIC_VERTEX,
	ANIMATED_VERTEX,
	GUI_VERTEX,

	DEBUG_VERTEX,
};


struct dVertex 
{
	Vec3 position;
	Vec3 color;
};

struct gVertex
{
	Vec3 position;
	Vec3 color;
	Vec2 uv;
};

struct sVertex
{
	Vec3 position;
	Vec3 color;
	Vec3 normal;
	Vec2 uv;
};

struct aVertex
{
	Vec3  position;
	Vec3  color;
	Vec3  normal;
	Vec2  uv;

	IVec4 influenceIndices;
	Vec4  weights;
};