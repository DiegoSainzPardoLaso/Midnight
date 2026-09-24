#pragma once

#include "Camera.h"

#include "../Inputs/Inputs.h"

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "../Math/LinearAlgebra.h"

#include "../Rendering/Material.h"

#include "../ResourceHandling/MOFLoader.h"

#include "../Engine/EngineConfig.h"

#define MAX_CAMERAS_PER_SCENE 16

struct CameraSystem
{
	// @note Make it more dynamic? or just 16 cameras at any given time?
	//
	Camera  cameras[MAX_CAMERAS_PER_SCENE];
	Camera* activeCamera;

	int	   cameraCount;
	int	   activeCameraIdx;
};

namespace fCamera_System
{
	CameraSystem* Initialize();


	Camera& CreateCamera(CameraSystem *&camera_system, const Kind cameraType, const Vec3 cameraPosition, const float fov, const float movementSpeed, const float panSensitivity);
	void Update(CameraSystem *&camera_system, const Vec2& windowDimensions);

	void ChangeCamera(CameraSystem *&camera_system);

	namespace Internal
	{
		void SetupCamera_STRICTLY_FOR_SCENE_LOADING(CameraSystem *&camera_system, Camera &camera);
	}

}