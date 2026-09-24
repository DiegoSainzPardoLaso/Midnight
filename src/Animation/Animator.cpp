#include "Animator.h"

void  UpdateAnimator(Skeleton& skeleton, Animator& animator)
{
	if (animator.currentAnimation == nullptr) { return; }

	IncreaseAnimationTime(animator);
	CalculatePoseAndUpdateSkeleton(skeleton, animator);
}

void  AddAnimation(Animator& animator, Animation& animation)
{
	Animation* animations = reinterpret_cast<Animation*>(malloc(sizeof(Animation) * (animator.animationCount + 1)));
	for (unsigned int i = 0; i < animator.animationCount; i++) { animations[i] = animator.animations[i]; }
	animations[animator.animationCount] = animation;
	
	animator.animations = reinterpret_cast<Animation*>(malloc(sizeof(Animation) * (animator.animationCount + 1)));
	for (unsigned int c = 0; c <= animator.animationCount; c++) 
	{		
		animator.animations[c] = animations[c]; 
	}

	animator.animationCount++;
}

	  
void  SwitchAnimation(Animator& animator, Animation* animation) 
{
	animator.currentAnimation = animation; 
}


void  CalculatePoseAndUpdateSkeleton(Skeleton& skeleton, Animator& animator)
{
	Keyframe* currentFrame = GetCurrentFrame(animator);	
	//float   blend        = CalculateBlendBetweenFrames(currentFrame->timeStamp, animator.currentAnimationTime);
		 
	for (unsigned int jIdx = 0; jIdx < skeleton.jointsCount; jIdx++)
	{
		Joint& joint = skeleton.joints[jIdx];
		
		// @todo Interpolate positions rotations and scale
		//
		if (animator.currentAnimation->transformType == AnimationTransformType::Raw)
		{			
			joint.animatedTransform = currentFrame->transform[joint.idx];
			joint.skeletonTransform = joint.originalTransform * currentFrame->transform[joint.idx];
		}
		else
		{
			// @todo WIP
			//
			joint.animatedTransform = Identity();
		}
	}
}

float CalculateBlendBetweenFrames(float currentFrameTimeStamp, float currentAnimationTime)
{
	// @note As written before, each animation timeline has a frame in each timestamp of the animation
	// So if I get the currentFrameTimeStamp = 3, and the currentAnimationTime = 3.4
	// the current animation delta would always be bounded to 0-1, in this case, 0.4, so 40 percent of the animation
	//
	// printf("Substraction %f %f \n", currentAnimationTime,  currentFrameTimeStamp);
	// printf("FUCKING TIME %f \n", currentAnimationTime - currentFrameTimeStamp);
	return currentAnimationTime - currentFrameTimeStamp;
}

// @todo @HIM NOT FINISHED
Mat4  InterPolatePose(Keyframe* currentFrame, Keyframe* nextFrame, int idx, float blend)
{	
	Vec3 newPosition	= Lerp(currentFrame->position[idx],    nextFrame->position[idx],    blend);
	Quat newOrientation = Lerp(currentFrame->orientation[idx], nextFrame->orientation[idx], blend);
	Vec3 newScale   	= Lerp(currentFrame->scale[idx],	   nextFrame->scale[idx],       blend);

	return ScaleMatrix(newScale) * TranslationMatrix(newPosition);
}

// @todo @HIM NOT FINISHED
void  IncreaseAnimationTime(Animator& animator)
{		
	animator.currentAnimationTime += 30.0f * Time::DeltaTime();	
	if (animator.currentAnimationTime > animator.currentAnimation->frameCount) { animator.currentAnimationTime = 0.0f; }
}


Keyframe* GetCurrentFrame(Animator& animator)
{
	// Really // @important // @note This works, because .maf files have a frame asignated for the entirity of the animation
	// so an animation of length 54 would have 54 frames
	//
	int fIdx = (int)floor(animator.currentAnimationTime);
	
	return &animator.currentAnimation->keyFrames[fIdx];
}

Keyframe* GetNextFrame(Animator& animator)
{
	// @warning // @note Check this if the animation seems to jump between the last and first frame
	unsigned int nFIdx = (unsigned int)floor(animator.currentAnimationTime) + 1;
	if (nFIdx >= animator.currentAnimation->frameCount) { nFIdx = 2; }	
	return &animator.currentAnimation->keyFrames[nFIdx];
}