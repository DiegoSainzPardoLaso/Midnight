#pragma once


#include <vulkan/vulkan_raii.hpp>

#include "../Types/Mesh.h"
#include "../Rendering/Vulkan/Buffer.h"
#include "../Rendering/Vulkan/Descriptors.h"
#include "../Rendering/Vulkan/VulkanShader.h"
#include "../Rendering/Vulkan/VulkanPipeline.h"



struct Grid_VK
{
public:
	Grid_VK(const vk::raii::PhysicalDevice &physicalDevice, const vk::raii::Device &logicalDevice, const std::vector<uint32_t> familyQueueIndices, const vk::raii::CommandPool &commandPool, const vk::raii::DescriptorPool &descriptorPool, const vk::raii::Queue &transferQueue, vk::Format colorFormat, vk::Format depthFormat);

public:
	void Update(const Mat4 &view, const Mat4 &projection, const Vec3 &cameraPosition, const uint32_t currentFrameIdx);
	void Draw(vk::raii::CommandBuffer &commandBuffer, uint32_t currentFrameIdx);
					
public:
	Mesh<dVertex>						 mesh;	
	Shader_VK							 shader;	
	std::vector<vk::raii::DescriptorSet> descriptorSet; // This way of doing things accounts for VSYNC and Uncapped mode rendering
	Pipeline_VK							 pipeline;

	Buffer								 vertexBuffer;
	Buffer								 indexBuffer;
	std::vector<Buffer>					 mvpUBO;
};