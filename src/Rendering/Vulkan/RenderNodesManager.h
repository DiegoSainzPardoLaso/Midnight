#pragma once

#include <unordered_map>
#include <vector>


#include "Queue.h"
#include "Buffer.h"
#include "Descriptors.h"
#include "VulkanPipeline.h"

#include "RenderNode.h"


#include "../../Camera/CameraSystem.h"

struct RenderNodeSystem_VK
{
	std::vector<sRenderNode> cameraRenderNodes;
};

namespace fRenderNodeSystem
{
	RenderNodeSystem_VK *Create
	(
		const vk::raii::PhysicalDevice	    &physicalDevice, 
		const vk::raii::Device		        &logicalDevice, 
		const vk::raii::CommandPool	        &commandPool, 
		const vk::raii::Queue			    &transferQueue, 
		const std::vector<uint32_t>	        &familyQueueIndices,
		
	    const vk::raii::DescriptorPool      &descriptorPool,
	    const vk::raii::DescriptorSetLayout &descriptorSetLayout,
		
		CameraSystem						*&camera_system
	);
	
	void Draw(sRenderNode &node, vk::raii::CommandBuffer &commandBuffer, vk::raii::Pipeline &pipeline, vk::raii::PipelineLayout &pipelineLayout, uint32_t currentFrameIdx);	
	

	void Clear(RenderNodeSystem_VK *&renderNodes);
}



class Render_Node_Agent
{
	//===================================================================//
	// Vulkan Specific members Pointers									 //
	//===================================================================//
	//
	vk::raii::PhysicalDevice		           *physical_device;
	vk::raii::Device				           *logical_device;
									           
	Queue							           *graphics_queue;
	Queue							           *transfer_queue;
	vk::raii::CommandPool			           *transfer_commands_pool;
									           
	vk::raii::DescriptorPool		           *descriptor_pool;
	//
	//===================================================================//
	//
	vk::Format								    color_surface_format;
	vk::Format								    depth_surface_format;
	//
	//===================================================================//
	//
	std::unordered_map<std::string, Shader_VK>					shaders;
	std::unordered_map<uint32_t, vk::raii::DescriptorSetLayout> descriptor_set_layouts; // Use the shader_metadata bindings hash
	std::unordered_map<uint32_t, Pipeline_VK>				    pipelines;			    // Use the shader_metadata bindings hash
	//
	//===================================================================//
	//
	std::vector<Static_Render_Node> static_nodes;


public:
	Render_Node_Agent(vk::raii::PhysicalDevice &physical_device, vk::raii::Device &logical_device, Queue &graphics_queue, Queue &transfer_queue, vk::raii::CommandPool &transfer_command_pool, vk::raii::DescriptorPool &descriptor_pool, vk::Format color_format, vk::Format depth_format);
   ~Render_Node_Agent();

public:	
	void create_node(Mesh<sVertex> &mesh, Transform &transform, Material_VK &material);		
	void update_nodes(const Mat4 &view, const Mat4 &projection, const uint32_t current_frame);
	void draw_nodes(const vk::raii::CommandBuffer &command_buffer, const uint32_t current_frame_idx);

private:	
	void update_mvp_ubos(const Mat4 &view, const Mat4 &projection, const uint32_t current_frame);
};