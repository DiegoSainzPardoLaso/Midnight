#include "CameraSystem.h"


CameraSystem *fCamera_System::Initialize()
{
	return new CameraSystem();
}


Camera& fCamera_System::CreateCamera(CameraSystem *&camera_system, const Kind cameraType, const Vec3 cameraPosition, const float fov, const float movementSpeed, const float panSensitivity)
{
	Camera camera;
	
	// ==============================================
	// Mesh
	// ==============================================
	const char *meshPath     = "C:/Midnight/resources/Engine/camera/camera.mof";
	
	MOFLoader::Data meshData = MOFLoader::LoadMesh(meshPath);
	camera.mesh			     = meshData.staticMesh;
#if CURRENT_RENDERING_API == OPENGL
	camera.material			 = fMaterial::Create("C:/Midnight/shaders/glsl/sDefault.shader");	

#elif CURRENT_RENDERING_API == VULKAN
	camera.material			 = fMaterial::Create("C:/Midnight/shaders/slang/test.shader");
#endif

	// ==============================================
	// Config
	// ==============================================
	camera.index				 = camera_system->cameraCount;
		
	camera.transform.position    = cameraPosition;
	camera.transform.orientation = Quat();
	camera.transform.scale		 = { 1,1,1 };
	camera.transform			 = fTransform::Initialize(cameraPosition, { 0, 0, 0 }, {1,1,1});
	camera.lerpingPosition		 = cameraPosition;

	camera.projection			 = PerspectiveProjectionMatrix(WIDTH, HEIGHT, fov, ZNEAR, ZFAR);
	camera.fov					 = fov;

	camera.panSensitivity		 = panSensitivity;
	camera.movementSpeed		 = movementSpeed;
	camera.originalMovementSpeed = movementSpeed;
	camera.newMovementSpeed		 = movementSpeed * 2.5f;

	camera.yaw					 = -90.0f;
	camera.pitch				 = 0.0f;
	camera.lerpingDirectionAlpha = 0;

	// Offset to make the camera look in the Y direction
	camera.lookTarget			 = Vec3(camera.transform.position.x, camera.transform.position.y - 3.0f, camera.transform.position.z);	
								 
	Vec3 worldUp				 = Vec3(0.0f, 0.0f, 1.0f);
	camera.direction			 = Normalize(camera.transform.position - camera.lookTarget);
	camera.lookTarget			 = Normalize(camera.lookTarget);
	camera.right			     = Normalize(Cross(worldUp, camera.direction));
	camera.worldUp				 = worldUp;
	camera.localUp			     = Normalize(Cross(camera.direction, camera.right));

	camera.lerpingDirectionUsedForViewMatrix		 = camera.direction;

	camera.kind					 = cameraType;
	camera.state				 = Still;

	camera_system->cameras[camera_system->cameraCount] = camera;
	camera_system->activeCamera    = &camera_system->cameras[camera_system->cameraCount];
	camera_system->activeCameraIdx = camera_system->cameraCount;
	camera_system->cameraCount++;

	return camera_system->cameras[camera_system->cameraCount - 1];
}
 

void fCamera_System::Update(CameraSystem *&camera_system, const Vec2 &window)
{				
	ChangeCamera(camera_system);

	switch (camera_system->activeCamera->kind)
	{
		case Kind::Viewport:
		{
			Camera &camera = *camera_system->activeCamera;
			fCameraViewport::Update(camera);			

			Vec3 eulerOrientation        = { 0, camera.pitch, -camera.yaw };
			camera.transform.orientation = EulerToQuaternion(eulerOrientation.x, eulerOrientation.y, eulerOrientation.z);
			
			Vec3 lookAtPosition = camera.transform.position + camera.lerpingDirectionUsedForViewMatrix;
			camera.view         = ViewMatrix(camera.transform.position, lookAtPosition, camera.worldUp);

			if	 (window.width != 0 && window.height != 0) { camera.projection = PerspectiveProjectionMatrix((int)window.width, (int)window.height, camera.fov, ZNEAR, ZFAR); }
			else										   { camera.projection = PerspectiveProjectionMatrix(WIDTH,		             HEIGHT,		camera.fov, ZNEAR, ZFAR); }

		} break;
	}
}


void fCamera_System::ChangeCamera(CameraSystem *&camera_system)
{
	if (fInput::FirstPress(KEY_RIGHT))
	{	
		// I do this to update the model matrix		
		fTransform::Update
		(
			camera_system->activeCamera->transform,
			camera_system->activeCamera->transform.position, 
			camera_system->activeCamera->transform.orientation, 
			camera_system->activeCamera->transform.scale
		); 

		camera_system->activeCameraIdx = (camera_system->activeCameraIdx + 1) % camera_system->cameraCount;
		camera_system->activeCamera    = &camera_system->cameras[camera_system->activeCameraIdx];		
	}
	if (fInput::FirstPress(KEY_LEFT))
	{	
		// I do this to update the model matrix
		fTransform::Update
		(
			camera_system->activeCamera->transform,
			camera_system->activeCamera->transform.position, 
			camera_system->activeCamera->transform.orientation, 
			camera_system->activeCamera->transform.scale
		);

		camera_system->activeCameraIdx = camera_system->activeCameraIdx - 1 >= 0 ? camera_system->activeCameraIdx - 1 : camera_system->cameraCount - 1;
		camera_system->activeCamera    = &camera_system->cameras[camera_system->activeCameraIdx];		
	}	
}


void fCamera_System::Internal::SetupCamera_STRICTLY_FOR_SCENE_LOADING(CameraSystem *&camera_system, Camera &camera)
{
	// ==============================================
	// Mesh
	// ==============================================		
	MOFLoader::Data meshData = MOFLoader::LoadMesh(""); // @warning
	camera.mesh              = meshData.staticMesh;
	camera.material          = fMaterial::Create(camera.material.shaderPath);	

	// ==============================================
	// Config
	// ==============================================
	camera.index                      = camera_system->cameraCount;	
	camera.transform                  = fTransform::Initialize(camera.transform.position, camera.transform.orientation, camera.transform.scale);

	camera.projection                 = PerspectiveProjectionMatrix(WIDTH, HEIGHT, camera.fov, ZNEAR, ZFAR);	
								      	
	camera.originalMovementSpeed      = camera.movementSpeed;
	camera.newMovementSpeed		      = camera.movementSpeed * 2.5f;
								      	
	Vec3 worldUp                      = Vec3(0.0f, 0.0f, 1.0f);	
	camera.right					  = Normalize(Cross(worldUp, camera.direction));
	camera.worldUp                    = worldUp;
	camera.localUp					  = Normalize(Cross(camera.direction, camera.right));
						              
	
	camera_system->cameras[camera_system->cameraCount] = camera;
	camera_system->activeCamera                       = &camera_system->cameras[camera_system->cameraCount];
	camera_system->activeCameraIdx                    = camera_system->cameraCount;
	camera_system->cameraCount++;

	camera_system->cameras[camera_system->cameraCount - 1];
}