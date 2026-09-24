#pragma once

#include "../Camera/CameraSystem.h"

#include "../Rendering/Material.h"

#include "../Physics/Physics.h"
#include "../Physics/Types/Ray.h"
#include "../Physics/Types/Plane.h"

#include "../ResourceHandling/MOFLoader.h"
#include "../Rendering/OpenGL/OGLUtilities.hpp"
#include "../Rendering/OpenGL/RenderableObjectsManager.h"

#include "../Inputs/Inputs.h"
#include "../Engine/EngineConfig.h"

#include "../Math/Matrix.h"
#include "../Math/Vector.h"


#define CTRL_SNAP_ROTATION_DEGREES		  15.0f
#define CTRL_SHIFT_SNAP_ROTATION_DEGREES  5.0f
#define SHIFT_SNAP_ROTATION_DEGREES		  0.1f

enum GIZMOS_TRANSFORMATION : byte
{
	NO_TRANSFORMATION,

	TRANSLATION,
	ROTATION,
	SCALING,


	CONTEXTUAL_TRANSLATION,
	CONTEXTUAL_ROTATION,
	CONTEXTUAL_SCALING,
};

struct PICKER_DATA	
{
	int objectType;
	int objectIndex;
	int triangleIndex;
};

struct Picker
{
	GLuint frameBufferObjectID;
	GLuint pickingColorTextureID;
	GLuint depthTextureID;

	PICKER_DATA retrievedPixelInformation;
};

struct Gizmos
{	
	Picker	   pickerBuffer;

	// @note The AABB bBoxTSXYZ and xyzLine's are use in both the translation and the scale gizmos
	//
	StaticMesh visualTranslationX; 
	StaticMesh visualTranslationY; 
	StaticMesh visualTranslationZ; 
	
	StaticMesh visualRotationX;
	StaticMesh visualRotationY;
	StaticMesh visualRotationZ;

	StaticMesh visualScalingX;
	StaticMesh visualScalingY;
	StaticMesh visualScalingZ;

	StaticMesh selectableTranslationX;
	StaticMesh selectableTranslationY;
	StaticMesh selectableTranslationZ;

	StaticMesh selectableRotationX;
	StaticMesh selectableRotationY;
	StaticMesh selectableRotationZ;

	StaticMesh selectableScalingX;
	StaticMesh selectableScalingY;
	StaticMesh selectableScalingZ;


	// StaticMesh visualPlaneXY;
	// StaticMesh visualPlaneXZ;
	// StaticMesh visualPlaneYZ;
	// 
	// StaticMesh selectablePlaneXY;
	// StaticMesh selectablePlaneXZ;
	// StaticMesh selectablePlaneYZ;


	StaticMesh pivotPoint;


	DebugShape xLine;
	DebugShape yLine;
	DebugShape zLine;

	 
	Material_OGL material;
	Transform	 transform;

	Ray   r;
	Plane p;
	Vec3  previousPlaneNormal;

	TRANSFORMATION_ORIENTATION transformationOrientation;
	GIZMOS_TRANSFORMATION      currentTransformation;
	GIZMOS_TRANSFORMATION      lastTransformation;
	ENGINE_AXIS			       hoveringAxis;
	ENGINE_AXIS			       currentTransformationAxis;
	ENGINE_AXIS			       previousTransformationAxis;
						       
	PICKER_DATA			       retrievedDataInformation;		// @note I use this to retain the selected object as the picker doesnt care about the gizmos state	
						       
	MDF_KEY				       previousModKey;					// @note I use this one, to transition between the different mod keys	
	
	Vec3				       startingIntersectionPoint;		
	Vec3				       startingActiveObjectPosition;	
	Vec3				       startingActiveObjectScale;		
	Quat				       startingActiveObjectOrientation;	

	Vec3				       ogObjectPositionForReseting;
	Vec3				       ogObjectScaleForReseting;
	Quat				       ogObjectOrientationForReseting;		
	
	float					   rotationAngle;	
	bool					   snapRotationAngleOnce;			// @note I use this to snap the current orientation to closest compatible angle the first time a mdf key is pressed

	bool				       storeRelevantDataOnce;
	bool				       performingTransformation;

	std::string				   transformByInputStr;
	float					   transformByInputValue;
};



namespace fGizmos
{
	Gizmos *Initialize(Vec2 &windowDimensions);

	void Update(Gizmos *&gizmos, RenderNodeSystem_OGL *&renderNodes, CameraSystem *&camera_system, Vec2 &clientAreaDimensions);


	void SwitchBetweenWorldAndLocalTransformationsAndUpdateGizmosTransform(Gizmos *&gizmos, Vec3 &selectedObjectPosition, Quat &selectedObjectOrientation);
	void ResetTransformationsByInput(Gizmos *&gizmos, Transform *t);
	
	void MoveSelectedObject  (Gizmos *&gizmos, Transform *&selectedObjectTransform, Vec3 &intersectionPoint);
	void ScaleSelectedObject (Gizmos *&gizmos, Transform *&selectedObjectTransform, Vec3 &intersectionPoint);
	void RotateSelectedObject(Gizmos *&gizmos, Transform *&selectedObjectTransform, Vec3 &cameraPosition, Vec3 &intersectionPoint);

	void MoveSelectedObjectContextually  (Gizmos *&gizmos, Transform *&selectedObjectTransform, Vec3 &intersectionPoint);
	void RotateSelectedObjectContextually(Gizmos *&gizmos, Transform *&selectedObjectTransform, Vec3 &cameraPosition,  Vec3 &intersectionPoint);
	void ScaleSelectedObjectContextually (Gizmos *&gizmos, Transform *&selectedObjectTransform, Vec3 &intersectionPoint);
	

	namespace Helpers
	{		
		void UpdateGizmosTransformationAndAxisByInput(Gizmos *&gizmos);
		void UpdateGizmosPlane(Gizmos *&gizmos, Vec3 &newPosition, Vec3 &cameraDirection);
								
		void NASTY_TransformContextuallyByInput(Gizmos *&gizmos);
		
		Vec3  GetWorldTranslationBasedOnTheCurrentModKeys(Gizmos *&gizmos, Vec3 &selectedAxis, Vec3 &currentIntersectionPoint, Vec3 &inPosition);
		Vec3  GetLocalTranslationBasedOnTheCurrentModKeys(Gizmos *&gizmos, Vec3 &rotatedAxis, float distanceToPlane, Vec3 &inPosition);
		Vec3  GetScalingBasedOnTheCurrentModKeys(Gizmos *&gizmos, Vec3 &selectedAxis, float distanceToPlane, Vec3 &inScale);
		float GetRotationAngleBasedOnTheCurrentModKeys(Gizmos *&gizmos, float rotationAngle, Vec3 &currentIntersectionPoint);		

		void StopTransformationsFromBleedIntoEachOther(Gizmos *&gizmos, Transform *&selectedTransform);

		Vec3 GetSelectedAxisVector(Gizmos *&gizmos);
		Vec3 GetSelectedAxisVector(Gizmos *&gizmos, Vec3 &fallback);
		
		Transform *GetSelectedObjectTransform(PICKER_DATA &dataInfo, CameraSystem *&camera_system);		

		void ClearGizmosState(Gizmos *&gizmos);

		void SetGizmosLines(Gizmos *&gizmos, ENGINE_AXIS axis, Vec3 &position, Vec3 &rotationAxis);
		void ClearGizmosLines(Gizmos *&gizmos);
		
	}




	// The Information that can be retrieved with a pixel is:
	//		- Type		 : Object Identification type, e.g Cameras, entities...
	//		- ID		 : Inside an array of objects of the same type
	//		- Triangle ID: Triangle Id
	//

	namespace fPicker
	{
		Picker InitializePicker(Vec2 &windowDimensions);

		void Update(Gizmos *&gizmos, CameraSystem *&camera_system, RenderNodeSystem_OGL *&renderableManager, Vec2 &wDimensions);

		ENGINE_TYPE GetSelectedObjectType(int retrievedObjectType);


		namespace Internal
		{
			inline Vec2   PREVIOUS_DIMENSIONS;
			inline Shader PICKER_SHADER;


			void EnableWritingIntoThePickerFrameBufferTexture(Picker &picker);

			void Draw(unsigned int &VAO, int index_count, int objectType, int objectIndex, Mat4 &model, Camera *&activeCamera);

			void DisableWritingIntoThePickerFrameBufferTexture();

			PICKER_DATA ReadPixel(Picker &picker, unsigned int x, unsigned int y, Vec2 &wDimensions);

			void RedimensionPickerFrameBuffer(Picker &picker, Vec2 &wDimensions);
		}
	}
}