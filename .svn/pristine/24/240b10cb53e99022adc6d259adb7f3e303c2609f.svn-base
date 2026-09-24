#pragma once

#include <iostream>

#include <cstdint>
#include <algorithm>

#define VK_USE_PLATFORM_WIN32_KHR
#define VULKAN_HPP_HANDLE_ERROR_OUT_OF_DATE_AS_SUCCESS				// @note This one is set because, the present Queue crashes when closing the window... I don't know why though
#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include "VulkanConfig.h"

#include "Memory.h"

#include "SwapChain.h"
#include "DepthBuffer.h"

#include "VulkanImage.h"

#include "Descriptors.h"
#include "VulkanShader.h"

#include "UniformBufferObjectTypes.h"
#include "Buffer.h"
#include "CommandBuffers.h"

#include "Extensions.h"
#include "DebugMessenger.h"

#include "VulkanPipeline.h"


#include "Queue.h"
#include "Pools.h"


#include "../Shared/enums.h"

#include "../../File/File.h"
#include "../../Inputs/Inputs.h"
#include "../../Math/Vector/Vector2.h"
#include "../../Math/Vector/Vector3.h"


#include "../../Grid/GridVK.hpp"

// Used to load Vulkan-1.dll
//
extern PFN_vkCreateInstance VULKAN_DLL;

extern bool						 ENABLE_VALIDATION_LAYERS;
extern std::vector<const char *> VALIDATION_LAYERS;
extern std::vector<const char *> PHYSICAL_DEVICE_REQUIRED_EXTENSIONS;
extern std::vector<const char *> LOGICAL_DEVICE_REQUIRED_EXTENSIONS;
extern std::vector<const char *> VULKAN_REQUIRED_EXTENSIONS;
extern std::vector<vk::Format>	 POSSIBLE_SUPPORTED_DEPTH_FORMATS;
extern vk::ImageTiling			 DEPTH_IMAGE_TILING;

extern uint32_t  CURRENT_FRAME_INDEX;
extern Grid_VK  *GRID_VK;



class Vulkan_Renderer
{
public:
	//
	//
	vk::raii::Instance					 vulkan_instance	   = nullptr;
	vk::raii::Context					 vulkan_context;
	//
	//
	//
	vk::raii::PhysicalDevice			 physical_device	   = nullptr;
	vk::raii::Device					 logical_device		   = nullptr;
	vk::raii::SurfaceKHR				 window_surface		   = nullptr;

	vk::DebugUtilsMessengerEXT			 debug_messenger;
	//
	//
	//
	Swap_Chain							 swap_chain			   = nullptr;
	Depth_Buffer						 depth_buffer;
	//
	//
	//
	vk::raii::CommandPool				 graphics_command_pool = nullptr;
	vk::raii::CommandPool				 transfer_command_pool = nullptr;

	std::vector<vk::raii::CommandBuffer> graphics_command_buffer;
	//
	//
	//
	vk::raii::DescriptorPool			 descriptors_pool	   = nullptr;
	//
	//
	//
	Queue								 graphics_and_presentation_queue;
	Queue								 transfer_queue;
	//
	//
	//
	std::vector<vk::raii::Semaphore>     present_complete_signal_semaphore{};
	std::vector<vk::raii::Semaphore>     render_finished_signal_semaphore{};
	std::vector<vk::raii::Fence>	     draw_signal_fence{};
	//
	//
	//
	//Grid_VK							 grid;
	Render_Node_Agent					*render_nodes_agent;
	//
	//
	//
	RENDERING_MODE						 current_rendering_mode;
	Vec2								 current_dimensions;
	Vec3								 background_color;
	//
	//
	//
public:	
	 
	Vulkan_Renderer(const HWND &window_handle, const Vec2 &window_dimensions, const Vec3 &new_background_color);
   ~Vulkan_Renderer();

public:		
	void update(const Mat4 &view, const Mat4 &projection, const Vec2 &new_window_dimensions);
	void draw();


private:
	void load_vulkan();
	void create_vulkan_instance();
	void pick_physical_device();
	void create_window_surface(const HWND &window_handle);
	void set_up_queues_and_create_logical_device();
	void set_up_synchronization_objects();

	bool check_if_the_desired_validation_layers_are_available(std::vector<const char *> validationLayers);
	std::vector<const char *> check_needed_extensions_availability_and_retrieve_them(std::vector<const char *> &extensions);

	void recreate_swap_chain_and_depth_buffer(const Vec2 &window_dimensions);
	void update_rendering_mode();
};



 





 
 
 







//=====================// 
// REMOVE WHEN FINISH  //
//=====================// 
//
void UpdateMVP_UBO(RenderNodeSystem_VK *&renderNodesManager, Mat4 &view, Mat4 &projection, uint32_t currentFrame);
extern vk::raii::DescriptorSetLayout		descriptorSetLayout;
extern vk::raii::Pipeline					SHADER_PIPELINE;
extern vk::raii::PipelineLayout				SHADER_PIPELINE_LAYOUT;

namespace fVulkan
{
	void Initialize(HWND &handle, Vec2 &windowDimensions, RenderNodeSystem_VK *&renderableObjectsManager, CameraSystem *&camera_system, Vulkan_Renderer *&v_renderer);
	void Draw(RenderNodeSystem_VK *&renderableObjectsManager, Camera *&activeCamera, Vec2 &windowDimensions, Vulkan_Renderer *&v_renderer);
	 
}
//
//=====================// 



 