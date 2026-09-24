#pragma once

#include <iostream>

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include "VulkanImage.h"

struct Depth_Buffer
{
	Image_VK   image;	
	vk::Format format;
};

namespace fDepth_Buffer
{
	Depth_Buffer Create(vk::raii::PhysicalDevice &physicalDevice, vk::raii::Device &logicalDevice, vk::Extent2D extent, std::vector<vk::Format> &possibleSupportedFormats, vk::ImageTiling tiling);
	void		Recreate(vk::raii::PhysicalDevice &physicalDevice, vk::raii::Device &logicalDevice, Depth_Buffer &depthBuffer, vk::Extent2D extent, vk::ImageTiling tiling);
	void		Clear(Depth_Buffer &depthBuffer);

	namespace Internal
	{
		vk::Format FindSupportedDepthBufferFormat(vk::raii::PhysicalDevice &physicalDevice, vk::raii::Device &logicalDevice, std::vector<vk::Format> &possibleSupportedFormats, vk::ImageTiling tiling, vk::FormatFeatureFlags features);

		bool HasStencilComponent(vk::Format depthBufferFormat);
	}
}