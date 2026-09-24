#include "Skeleton.h"

Skeleton fSkeleton::Create(int jointCount)
{
	Skeleton skeleton{};
	skeleton.joints		 = reinterpret_cast<Joint*>(malloc(sizeof(Joint) * jointCount));
	skeleton.jointsCount = jointCount;

	skeleton.jointFlatData = reinterpret_cast<float*>(malloc(sizeof(float) * skeleton.jointsCount * 16));

	return skeleton;
}

void fSkeleton::Update(Skeleton& skeleton)
{
	for (unsigned int i = 0; i < skeleton.jointsCount; i++)
	{
		for (unsigned int m = 0; m < 16; m++)
		{
			skeleton.jointFlatData[i * 16 + m] = skeleton.joints[i].animatedTransform.data[m];
		}
	}
}


// @note Clever way of not running through all the array, and the joints, will be added sequentially, as
// the mof loader, runs trough the file
//
void fSkeleton::AddJoint(Skeleton& skeleton, Joint& joint, uint32_t idxInsideTheSkeletonJointArray)
{
	if (skeleton.jointsCount == 0 || idxInsideTheSkeletonJointArray > skeleton.jointsCount) { return; }

	skeleton.joints[idxInsideTheSkeletonJointArray] = joint;
}

Joint* fSkeleton::GetJoint(Skeleton& skeleton, uint32_t index)
{
	assert(index < skeleton.jointsCount);

	return &skeleton.joints[index];
}


 