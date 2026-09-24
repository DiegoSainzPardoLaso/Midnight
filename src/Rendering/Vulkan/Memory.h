#pragma once

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include <iostream>

namespace fMemory
{
	uint32_t FindMemoryType(const vk::raii::PhysicalDevice &physicalDevice, const uint32_t memoryTypeBits, const vk::MemoryPropertyFlags properties);
}