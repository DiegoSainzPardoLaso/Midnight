#pragma once

#include <string>
// ============================================
// Enums
// ============================================
enum ENGINE_TYPE
{
	NONE,
	CAMERA,

	GIZMOS_TRANSLATION,
	GIZMOS_ROTATION,
	GIZMOS_SCALING,

	ANIMATED_ENTITY,
	STATIC_ENTITY,
};

enum ENGINE_AXIS
{
	NO_AXIS,
	X,
	Y,
	Z,
	XY,
	XZ,
	YZ,
	CUSTOM,
};

enum TRANSFORMATION_ORIENTATION
{
	WORLD,			// The Axis are X <1, 0, 0>  - Y <0, 1, 0> - Z <0, 0, 1>
	LOCAL,			// The Axis are whatever the rotation of the selected transform is
	// EULER,
	// ...
};

enum PRIMITIVE_TYPE
{
	INTEGER,
	FLOATING_POINT,
	STRUCTURE,
};


// ============================================
// Config
// ============================================
#define OPENGL  0
#define VULKAN  1

#define CURRENT_RENDERING_API VULKAN

extern float WIDTH;
extern float HEIGHT;
extern float FOV;
extern float ZNEAR;
extern float ZFAR;
extern float ASPECT;

extern float MAX_FPS;
extern float MAX_DELTA_TIME_PERIOD;
extern bool  VSYNC;

// ============================================

extern bool WRAP_MOUSE_X_RIGHT;
extern bool WRAP_MOUSE_X_LEFT;
extern bool WRAP_MOUSE_Y;

// ============================================
// Paths
// ============================================
extern std::string DEFAULT_OPENGL_SHADER_PATH;
extern std::string DEFAULT_MESH_PATH;
extern const char *DEFAULT_FONT_FNT;
extern const char *DEFAULT_FONT_ATLAS;

// ============================================
// Scene
// ============================================
extern std::string SCENE_ASCII_EXT;
extern std::string SCENE_BIANRY_EXT;




// ============================================
// Structs
// ============================================


// ============================================
// Macros
// ============================================
#define MOSTLY_SAME_PICKER_DATA(p0, p1) p0.objectType == p1.objectType && p0.objectIndex == p1.objectIndex
#define EXACT_SAME_PICKER_DATA (p0, p1) p0.objectType == p1.objectType && p0.objectIndex == p1.objectIndex && p0.triangleIndex == p1.triangleIndex

#define VALID_ENGINE_TYPE(type) type == ENGINE_TYPE::CAMERA || type == ENGINE_TYPE::ANIMATED_ENTITY || type == ENGINE_TYPE::GIZMOS