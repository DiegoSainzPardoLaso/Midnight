#pragma once

#include <chrono>
#include <string>

#include "../Camera/CameraSystem.h"
#include "../Camera/Camera.h"
#include "../Math/Vector.h"

#include "../Serializer/Serializer.h"
#include "../Utilities/Utilities.hpp"

#include "../ResourceHandling/MOFLoader.h"
#include "../ResourceHandling/MAFLoader.h"


enum SceneSerializationType
{
	BINARY,
	ASCII,
};

// @note Helper struct, just to populate all the other systems
//
struct Scene
{
	char  *date;
	char  *name;

	CameraSystem *camera_system;	
};


namespace fScene
{
	void Update(const char *sceneSavePath, bool &save, const char *loadPath, bool &load, CameraSystem *&camera_system);

	void default_scene(CameraSystem *&camaraSystem);

	void SerializeScene(const char *sceneSavePath, CameraSystem *&camera_system);
	Scene LoadScene(const char *scenePath);

	namespace Internal
	{
		Scene LoadASCIIScene(const char *scenePath);
		void LoadBinaryScene(const char* scenePath);

		void SerializeASCIIScene(const char *scenePath, CameraSystem *&camera_system);
		void SerializeBinaryScene(const char *scenePath, CameraSystem *&camera_system);
	}
}