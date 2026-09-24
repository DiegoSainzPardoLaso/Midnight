#include "Scene.h"

void fScene::default_scene(CameraSystem *&camera_system)
{	
	fCamera_System::CreateCamera(camera_system, Kind::Viewport, {  0,  6, 10 }, 90, 10, 25);
	fCamera_System::CreateCamera(camera_system, Kind::Viewport, { 10,  0,  0 }, 90, 10, 25);
	fCamera_System::CreateCamera(camera_system, Kind::Viewport, {  0, -6,  1 }, 90, 10, 25);
}


void fScene::Update(const char *sceneSavePath, bool &save, const char *loadPath, bool &load, CameraSystem *&camera_system)
{
	if (save)
	{
		SerializeScene(sceneSavePath, camera_system);		
		save = false; // @important THIS IS THE fOSM::InterestValues::SCENE_MUST_BE_SAVED variable
	}
	if (load)
	{
		free(camera_system);

		Scene newScene = LoadScene(loadPath);
		camera_system = newScene.camera_system;

		load = false; // @important THIS IS THE fOSM::InterestValues::SCENE_MUST_BE_LAODED variable
	}
}


void fScene::SerializeScene(const char *sceneSavePath, CameraSystem *&camera_system)
{	
	std::string ext = tFile::get_extension(sceneSavePath);

	if (!ext.compare(SCENE_ASCII_EXT)) { Internal::SerializeASCIIScene(sceneSavePath,  camera_system);  }
	else							   { Internal::SerializeBinaryScene(sceneSavePath, camera_system); }
}

Scene fScene::LoadScene(const char *scenePath)
{
	std::string ext = tFile::get_extension(scenePath);

	if (!ext.compare(SCENE_ASCII_EXT)) { return Internal::LoadASCIIScene(scenePath);  }
	else							   { Internal::LoadBinaryScene(scenePath); }	

	return Scene{};
}


Scene fScene::Internal::LoadASCIIScene(const char *scenePath)
{
	std::ifstream  file(scenePath, std::ios::in);
	std::string    line;
	int indentationLevel = 0;
	// ====================================
	// Information To Retrieve
	// ====================================
	ENGINE_TYPE type = ENGINE_TYPE::NONE;		// Main Type e.x. Cameras, Entities ...

	// ====================================
	// Objects to use for retrieving info
	// ====================================
	Camera tmpCamera;			

	// ====================================
	// New State
	// ====================================
	Scene sData;
	sData.camera_system = fCamera_System::Initialize();	


	while (std::getline(file, line))
	{
		std::vector<std::string> tokens = fUtil::TokenizeLine(line, ' ', '\t', NULL);
		
		if (tokens.size() > 1)
		{

			// ====================================
			// Camera
			// ====================================
			if (type == ENGINE_TYPE::CAMERA)
			{																	
				if (!tokens[0].compare("shader_path"))		 { strcpy(tmpCamera.material.shaderPath, tokens[1].c_str());													}
				if (!tokens[0].compare("position"))          { tmpCamera.transform.position         = { std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]) };	}
				if (!tokens[0].compare("euler_orientation")) { tmpCamera.transform.orientation		= { std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]), std::stof(tokens[5]) }; }
				if (!tokens[0].compare("scale"))		     { tmpCamera.transform.scale            = { std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]) };	}

				if (!tokens[0].compare("direction"))         { tmpCamera.direction      = { std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]) }; }
				if (!tokens[0].compare("look_target"))       { tmpCamera.lookTarget     = { std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]) }; }
				if (!tokens[0].compare("yaw"))               { tmpCamera.yaw            = std::stof(tokens[1]); }
				if (!tokens[0].compare("pitch"))             { tmpCamera.pitch          = std::stof(tokens[1]); }
				if (!tokens[0].compare("fov"))               { tmpCamera.fov            = std::stof(tokens[1]); }
				if (!tokens[0].compare("movement_speed"))    { tmpCamera.movementSpeed  = std::stof(tokens[1]); }
				if (!tokens[0].compare("pan_sensitivity"))   { tmpCamera.panSensitivity = std::stof(tokens[1]); }
				if (!tokens[0].compare("kind"))            
				{
					tmpCamera.kind = (Kind)std::stoi(tokens[1]); 
					fCamera_System::Internal::SetupCamera_STRICTLY_FOR_SCENE_LOADING(sData.camera_system, tmpCamera);
				}
			}			


			// ====================================
			// Type Identification
			// ====================================
			if (!tokens[1].compare("Camera"))  { type = ENGINE_TYPE::CAMERA; }
		}
	}

	return sData;
}


void fScene::Internal::LoadBinaryScene(const char *scenePath)
{

}

void fScene::Internal::SerializeASCIIScene(const char *scenePath, CameraSystem *&camera_system)
{
	unsigned int indentationLevel = 0;
	std::ofstream file(scenePath, std::ios::out);

	const auto now	       = std::chrono::system_clock::now();
	const std::time_t time = std::chrono::system_clock::to_time_t(now);

	file << std::ctime(&time) << "{\n";
	file << "\tname: " << tFile::get_name(scenePath) << "\n\n";
	indentationLevel++;

	// ===============================================
	// Cameras
	// ===============================================
	file << "\tcamera count:" << camera_system->cameraCount << "\n";
	for (int cameraIdx = 0; cameraIdx < camera_system->cameraCount; cameraIdx++)
	{
		SerializeCamera(file, camera_system->cameras[cameraIdx], indentationLevel);
	}

	file << "}";
	file.close();
}

void fScene::Internal::SerializeBinaryScene(const char *scenePath, CameraSystem *&camera_system)
{
}
