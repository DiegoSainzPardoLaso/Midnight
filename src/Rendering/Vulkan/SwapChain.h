#pragma once

#include <iostream>

#define VK_USE_PLATFORM_WIN32_KHR
#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include "VulkanConfig.h"
#include "VulkanImage.h"

#include "../../Math/Vector/Vector2.h"

struct Swap_Chain
{
	vk::raii::SwapchainKHR				swap_chain = nullptr;

	vk::SurfaceFormatKHR				surface_format;
	vk::Extent2D						extent;

	std::vector<vk::Image>				images;
	std::vector<vk::raii::ImageView>	image_views;

	Swap_Chain(std::nullptr_t) : swap_chain(nullptr) {}
	Swap_Chain(const vk::raii::PhysicalDevice &physical_device, const vk::raii::Device &logical_device, const vk::raii::SurfaceKHR &window_surface, const vk::PresentModeKHR present_mode, const Vec2 &dimensions);

	void recreate(const vk::raii::PhysicalDevice &physicalDevice, const vk::raii::Device &logicalDevice, const vk::raii::SurfaceKHR &window_surface, const vk::PresentModeKHR present_mode, const Vec2 &window_dimensions);
	void clear();

private:
	void internal_create(const vk::raii::PhysicalDevice &physicalDevice, const vk::raii::Device &logicalDevice, const vk::raii::SurfaceKHR &window_surface, const vk::PresentModeKHR present_mode, const Vec2 &window_dimensions);
};