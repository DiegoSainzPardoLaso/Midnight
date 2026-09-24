#include "Serializer.h"

#define ADD_INDENTATION(ofstream, uniformCount) for (unsigned int nIdx = 0; nIdx < uniformCount; nIdx++) { ofstream << "\t"; }


void SerializeCamera(std::ofstream &file, Camera &camera, unsigned int indentationLevel)
{
	ADD_INDENTATION(file, indentationLevel) file << "type: Camera\n";
	ADD_INDENTATION(file, indentationLevel) file << "{\n";

	SerializeStaticMesh(file, camera.mesh,		indentationLevel + 1);
	SerializeMaterial  (file, camera.material,  indentationLevel + 1);
	SerializeTransform (file, camera.transform, indentationLevel + 1);
	
	ADD_INDENTATION(file, indentationLevel + 1) SerializeVec3ASCII(file, "direction   ",   camera.direction);	
	ADD_INDENTATION(file, indentationLevel + 1) SerializeVec3ASCII(file, "look_target ",   camera.lookTarget);

	ADD_INDENTATION(file, indentationLevel + 1) SerializeFloat(file, "yaw            ",  camera.yaw);
	ADD_INDENTATION(file, indentationLevel + 1) SerializeFloat(file, "pitch           ", camera.pitch);
																			          
	ADD_INDENTATION(file, indentationLevel + 1) SerializeFloat(file, "fov             ", camera.fov);
	ADD_INDENTATION(file, indentationLevel + 1) SerializeFloat(file, "movement_speed  ", camera.movementSpeed);
	ADD_INDENTATION(file, indentationLevel + 1) SerializeFloat(file, "pan_sensitivity ", camera.panSensitivity);
	ADD_INDENTATION(file, indentationLevel + 1) SerializeEnum (file, "kind            ", camera.kind);

	ADD_INDENTATION(file, indentationLevel) file << "}\n";
}


void SerializeStaticMesh(std::ofstream &file, StaticMesh &mesh, unsigned int indentationLevel)
{
	ADD_INDENTATION(file, indentationLevel)		file << "type: StaticMesh\n";
	ADD_INDENTATION(file, indentationLevel)		file << "{\n";
	
	// ADD_INDENTATION(file, indentationLevel + 1) file << "mesh_path " << mesh.path << "\n";
	
	ADD_INDENTATION(file, indentationLevel)		file << "}\n";
}

// @todo Textures and everything
//
void SerializeMaterial(std::ofstream &file, Material &material , unsigned int indentationLevel)
{
	ADD_INDENTATION(file, indentationLevel)		file << "type: Material\n";
	ADD_INDENTATION(file, indentationLevel)		file << "{\n";
	
	ADD_INDENTATION(file, indentationLevel + 1) file << "shader_path " << material.shaderPath << "\n";
	
	ADD_INDENTATION(file, indentationLevel)		file << "}\n";
}

// @todo Add regular quaternion orientation
//
void SerializeTransform(std::ofstream &file, Transform &transform, unsigned int indentationLevel)
{
	ADD_INDENTATION(file, indentationLevel) file << "type: Transform\n";
	ADD_INDENTATION(file, indentationLevel) file << "{\n";

	ADD_INDENTATION(file, indentationLevel + 1) SerializeVec3ASCII (file, "position   ", transform.position);
	ADD_INDENTATION(file, indentationLevel + 1) SerializeQuaternion(file, "orientation", transform.orientation);
	ADD_INDENTATION(file, indentationLevel + 1) SerializeVec3ASCII (file, "scale      ", transform.scale);

	ADD_INDENTATION(file, indentationLevel) file << "}\n";
}

void SerializeVec3ASCII(std::ofstream &file, const char* name, Vec3 &vec3)
{		
	file << name << " { " << vec3.x << ", " << vec3.y << ", " << vec3.z << " }\n";
}



void SerializeVec4ASCII(std::ofstream &file, const Vec4 &vec4)
{
	
}

void SerializeQuaternion(std::ofstream &file, const char *name, const Quat &quat)
{

}



void SerializeEnum(std::ofstream &file, const char *name, const int value)
{
	file << name << " " << value << "\n";
}

void SerializeFloat(std::ofstream &file, const char *name, const float value)
{
	file << name << " " << value << "\n";
}