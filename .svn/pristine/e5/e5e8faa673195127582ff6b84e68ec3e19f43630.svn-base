#pragma once

#include <vector>

#include "RenderableObject.h"

#include "../../Camera/CameraSystem.h"
#include "OGLUtilities.hpp"

// @note I should really implement an arena allocator, but this will work for now
//
struct RenderNodeSystem_OGL
{
	std::vector<StaticRendereableObjectOpenGL> cameras;
};


namespace fRenderableObjectsManager
{
	RenderNodeSystem_OGL *Initialize(CameraSystem *&camera_system);
	void Update(RenderNodeSystem_OGL *&nodes);
	void AddCamera(Camera &camera);
}