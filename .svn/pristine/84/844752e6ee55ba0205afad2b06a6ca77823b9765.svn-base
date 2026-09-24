#include "RenderableObjectsManager.h"

RenderNodeSystem_OGL *fRenderableObjectsManager::Initialize(CameraSystem *&camera_system)
{
	RenderNodeSystem_OGL *rM = new RenderNodeSystem_OGL();
	
	for (unsigned int i = 0; i < camera_system->cameraCount; i++)
	{
		Camera &camera = camera_system->cameras[i];
		rM->cameras.emplace_back(fRenderableObject::Create(camera.mesh, camera.material));
	}

	return rM;
}

void fRenderableObjectsManager::Update(RenderNodeSystem_OGL *&nodes)
{
	for (StaticRendereableObjectOpenGL &node : nodes->cameras)
	{
		fShader::Update(node.material.shader);
	}
}

void fRenderableObjectsManager::AddCamera(Camera &camera)
{

}



