#pragma once

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Math/Quaternion.h"


struct Transform
{
	Vec3 position;	
	Quat orientation;
	Vec3 scale;

	Mat4 model;
};

namespace fTransform
{
	void	  Initialize(Transform &transform);
	Transform Initialize();
	Transform Initialize(Vec3 position, Quat orientation, Vec3 scale);	
	Transform Initialize(Vec3 position, Vec3 eulerAngles, Vec3 scale);
	
	void UpdatePosition   (Transform &t, Vec3 position);
	void UpdateOrientation(Transform &t, Quat orientation);
	void UpdateOrientation(Transform &t, Vec3 eulerAngles);
	void UpdateScale	  (Transform &t, Vec3 scale);
	
	void UpdatePosition	  (Transform *t, Vec3 position);
	void UpdateOrientation(Transform *t, Vec3 eulerAngles);
	void UpdateOrientation(Transform *t, Quat orientation);
	void UpdateScale	  (Transform *t, Vec3 scale);	
	

	// Usefull for the animation system
	// 	
	void UpdateModelMatrix(Transform &transform);
	
	void Update(Transform &transform, Vec3 position, Quat orientation, Vec3 scale);
	void Update(Transform &transform, Vec3 position, Vec3 orientation, Vec3 scale);
	void Update(Transform *transform, Vec3 position, Quat orientation, Vec3 scale);				
}