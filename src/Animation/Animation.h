#pragma once

#include "Types/Keyframe.h"

enum AnimationTransformType
{
	Raw,		 // @note I precompute the joints transform during the export
	Hierarchical // @note I export the joints decomposed matrix relative to their parent, calculations need to happend to achieve the right transformation
};

struct Animation
{
	char*				   name;
	AnimationTransformType transformType;
	Keyframe*              keyFrames;
	float	               frameRate;
	unsigned int           frameCount;
	unsigned int           jointCount;
};