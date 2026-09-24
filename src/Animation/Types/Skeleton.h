#pragma once

#include <assert.h>

#include "Joint.h"

#include "../../Types/Transform.h"


struct Skeleton
{			
	Joint*    root;
	Joint*    joints;	  
	uint32_t  jointsCount;
	Transform transform;	

	float* jointFlatData;
};

namespace fSkeleton
{
	Skeleton Create(int jointCount);
	void	 Update(Skeleton& skeleton);

	Joint*   GetJoint(Skeleton& skeleton, uint32_t index);
	void	 AddJoint(Skeleton& skeleton, Joint& joint, uint32_t idxInsideTheSkeletonJointArray);
	float*   ReturnAflatMat4ArrayOfAllTheJointTransformations(Skeleton& skeleton);
	
	
	void InitializeDebugVisualization(Skeleton& skeleton);
	void UpdateDebugVisualization(Skeleton& skeketon);
}
