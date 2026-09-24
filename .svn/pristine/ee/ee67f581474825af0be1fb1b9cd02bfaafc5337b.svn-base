#pragma once

#include "Animation.h"

#include "Types/Skeleton.h"
#include "Types/Keyframe.h"

#include "../Time/Time.h"
#include "../Math/Matrix.h"

struct Animator
{
	Animation*   currentAnimation;
	Animation*   animations;
	float	     currentAnimationTime;
	unsigned int animationCount;
};

void	  UpdateAnimator(Skeleton& skeleton, Animator& animator);

void	  AddAnimation(Animator& animator, Animation& animation);
void	  SwitchAnimation(Animator& animator, Animation* animation);

void	  CalculatePoseAndUpdateSkeleton(Skeleton& skeleton, Animator& animator);
float	  CalculateBlendBetweenFrames(float currentFrameTimeStamp, float currentAnimationTime);
Mat4	  InterPolatePose(Keyframe* currentFrame, Keyframe* nextFrame, int idx, float blend);

void	  IncreaseAnimationTime(Animator& animator);

Keyframe* GetCurrentFrame(Animator& animator);
Keyframe* GetNextFrame(Animator& animator);