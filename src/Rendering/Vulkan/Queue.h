#pragma once

#include <iostream>

#include <vulkan/vulkan_raii.hpp>


struct Queue
{
	vk::raii::Queue queue = nullptr;
	uint32_t        index;	
};

namespace fQueue
{
	Queue					  create(const vk::raii::Device &logical_device, const vk::DeviceQueueCreateInfo &queue_create_info);
	vk::DeviceQueueCreateInfo get_device_queue_create_info(const vk::raii::PhysicalDevice &physical_device, const vk::raii::SurfaceKHR &window_surface, const vk::QueueFlags &required_queue_flags);
	vk::DeviceQueueCreateInfo get_device_queue_create_info(const vk::raii::PhysicalDevice &physical_device, const vk::raii::SurfaceKHR &window_surface, const vk::QueueFlags &required_queue_flags, const vk::QueueFlags &excluding_queue_flags);
}
