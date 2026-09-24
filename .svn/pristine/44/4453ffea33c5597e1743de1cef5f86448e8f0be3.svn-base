#pragma once


#include <fstream>

#include "../File/File.h"

#include "../Camera/Camera.h"

#include "../Types/Transform.h"
#include "../Rendering/Material.h"
#include "../Math/Quaternion.h"
#include "../Math/Vector.h"



void SerializeCamera(std::ofstream &file, Camera &camera, unsigned int indentationLevel);


void SerializeStaticMesh(std::ofstream &file, StaticMesh &mesh,      unsigned int indentationLevel);
void SerializeMaterial  (std::ofstream &file, Material   &material,  unsigned int indentationLevel);
void SerializeTransform (std::ofstream &file, Transform  &transform, unsigned int indentationLevel);


void SerializeVec3ASCII (std::ofstream &file, const char* name, Vec3 &vec3);
void SerializeVec4ASCII (std::ofstream &file, const Vec4 &vec4);
void SerializeQuaternion(std::ofstream &file, const char *name, const Quat &quat);

void SerializeEnum (std::ofstream &file, const char *name, const int value);
void SerializeFloat(std::ofstream &file, const char *name, const float value);