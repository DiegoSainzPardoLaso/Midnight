#pragma once

#include <algorithm>

#include "../Inputs/Inputs.h"
#include "../Time/Time.h"

#include "../Types/Mesh.h"
#include "../Types/Transform.h"
#include "../Rendering/Material.h"

#include "../Physics/Types/AABB.h"

#include "../Math/Matrix.h"
#include "../Math/Vector.h"
#include "../Math/Quaternion.h"
#include "../Math/LinearAlgebra.h"

enum Kind
{
	Viewport,
	FirstPerson,
	thirdPerson,
};

enum CameraState
{
	Still,
	Moving,
	Panning,
	Centering
};

struct Camera
{		
	StaticMesh mesh;
	Material   material;
	Transform  transform;
	Vec3	   lerpingPosition;
	float	   lerpingAlpha;
		
	Vec3  lookTarget;

	Vec3  direction;							// @note This is used for the raycasting aspect of the physics among other things. DO NOT INTERPOLATE. 
	Vec3  lerpingDirectionUsedForViewMatrix;	// @note This is only used for the view matrix, DO NOT USE IT FOR ANYTHING ELSE
	float lerpingDirectionAlpha;

			  
	Vec3  worldUp;
	Vec3  localUp;
	Vec3  right;
			  
	Mat4  view;
	Mat4  projection;

	int   index;

	float yaw;
	float pitch;

	float fov;
	float movementSpeed;
	float panSensitivity;
	float originalMovementSpeed;
	float newMovementSpeed;

	Kind		kind;
	CameraState state;
};

namespace fCameraViewport
{	
	void Update(Camera &camera);

	void Move(Camera &camera);
	void UpdateDirection(Camera &camera);
	void Pan(Camera &camera);
	void MoveToPoint(Camera &camera, Vec3 &p, float speed);


	void DebugCamera(Camera &camera);
}