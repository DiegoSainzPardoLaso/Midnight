#pragma once


#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>


#include "VulkanConfig.h"
#include "VulkanVertex.h"

struct Pipeline_VK
{
	vk::raii::Pipeline		 pipeline = nullptr;
	vk::raii::PipelineLayout layout = nullptr;
};


namespace fPipeline_VK
{
	Pipeline_VK Create(const vk::raii::Device &logicalDevice, const RENDERING_MODE renderingMode, const VERTEX_TYPE vertexType, const vk::raii::ShaderModule &shaderModule, const vk::ShaderStageFlagBits *shaderStages, const uint32_t shaderStagesCount, const vk::raii::DescriptorSetLayout &descriptorSetLayout, const vk::Format colorFormat, const vk::Format depthFormat);

	namespace Internal
	{
		const char *ShaderStageName(vk::ShaderStageFlagBits shader_stage);
	}
}
