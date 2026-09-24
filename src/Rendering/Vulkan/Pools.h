#pragma once

#include <vulkan/vulkan_raii.hpp>

namespace fPool
{
	vk::raii::DescriptorPool create_descriptor_pool(const vk::raii::Device &logical_device, const uint32_t descriptor_pool_size);
	vk::raii::CommandPool    create_command_pool(const vk::raii::Device &logical_device, const uint32_t queue_family_index);
}

