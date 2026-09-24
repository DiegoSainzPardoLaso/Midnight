#pragma once

#include "../../Math/Matrix.h"

struct ModelViewProjectionUBO
{
	Mat4	 model;
	Mat4	 view;
	Mat4	 projection;
};



struct ViewProjectionCamUBO
{
	Mat4	 view;
	Mat4	 projection;
	Vec3	 cameraPosition;	
};