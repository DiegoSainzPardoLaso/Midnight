#include "EngineConfig.h"

float  WIDTH				 = 1920.f;
float  HEIGHT				 = 1080.0f;
float  FOV				     = 90.0f;
float  ZNEAR				 = 0.1f;
float  ZFAR				     = 1000.0f;
float  ASPECT				 = WIDTH / HEIGHT;
						  
float  MAX_FPS			     = 60.f;
float  MAX_DELTA_TIME_PERIOD = 1 / MAX_FPS;

bool   VSYNC				 = true;

// ============================================
// UI
// ============================================

bool WRAP_MOUSE_X_RIGHT = false;
bool WRAP_MOUSE_X_LEFT  = false;
bool WRAP_MOUSE_Y       = false;

// ============================================
// Paths
// ============================================
std::string DEFAULT_OPENGL_SHADER_PATH = "C:/Midnight/shaders/glsl/";
std::string DEFAULT_MESH_PATH		   = "C:/Midnight/resources/3dFiles/";
const char *DEFAULT_FONT_FNT		   = "C:/Midnight/resources/text/verdana.fnt";
const char *DEFAULT_FONT_ATLAS		   = "C:/Midnight/resources/text/verdana.png";

// ============================================
// Scene
// ============================================
std::string SCENE_ASCII_EXT  = ".mits";
std::string SCENE_BIANRY_EXT = ".mibs";