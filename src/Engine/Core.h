#pragma once

struct Window;
struct Console;
struct EDitorGUI;
struct Grid;
struct CameraSystem;
struct Gizmos;
struct RenderNodeSystem_OGL;
struct RenderNodeSystem_VK;
struct Vulkan_renderer;

struct Midnight_Engine_Core
{
	Window 				 *main_window;

	Console				 *console;
	
	EDitorGUI			 *gui;
	Grid 				 *grid;
	
	CameraSystem		 *camera_system;
	Gizmos				 *gizmos;

	RenderNodeSystem_OGL *renderNodesOGL;

	Vulkan_Renderer      *vulkan_renderer;
	RenderNodeSystem_VK	 *render_nodes_vulkan;
};