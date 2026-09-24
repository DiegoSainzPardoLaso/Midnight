#include "Joint.h"


Mat4 fJoint::CalculateInverseCharacterSpace(Joint& joint, Joint& root)
{	
	Mat4 parentSpace    = CalculateParentSpace(joint);
	Mat4 characterSpace	= root.originalTransform * parentSpace;
	return Inverse(characterSpace);
}
Mat4 fJoint::CalculateParentSpace(Joint& joint)
{
	return joint.originalTransform * joint.parent->originalTransform;
}

//Mat4 fJoint::CalculateCharacterSpace(Joint& joint, Joint& root)
//{
//	Mat4 pSpace = joint.parent->localSpace * joint.localSpace;
//	return root.localSpace * pSpace;
//}

// Mat4 fJoint::CalculateWorldSpace(Joint& joint)
// {
// 	return joint.parent->worldSpace * joint.localSpace;
// }
