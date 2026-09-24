#include "Ray.h"

// @note Bassically reverse matrix transformations without any matrix operations :D
//
Ray fRay::CastRayFromCamera(Vec3 &cameraPosition, Vec3 &cameraDirection, Vec3 &cameraRight, float cameraFOV, Vec2 &clientAreaDimensions, float rayLength)
{					        
	float a            = clientAreaDimensions.width / clientAreaDimensions.height;
	Vec3  ndc          = fInput::GetMouseNormalizedDeviceCoords(clientAreaDimensions);	
	
	float radFOV       = cameraFOV * PI / 180.0f;
	float fov		   = tan(radFOV / 2);

	Vec3  localUp	   = Cross(cameraRight, cameraDirection) * fov;
	Vec3  rightAr	   = cameraRight * a * fov;
	Vec3  rayDirection = cameraDirection + rightAr * ndc.x + localUp * ndc.y;	
	Normalize(rayDirection);

	return 
	{
		.p0		   = cameraPosition,
		.dir	   = rayDirection,
		.rayLength = rayLength
	};	
}
