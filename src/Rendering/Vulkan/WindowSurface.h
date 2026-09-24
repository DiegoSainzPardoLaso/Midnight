#pragma once


#define VK_USE_PLATFORM_WIN32_KHR
#define VULKAN_HPP_NO_CONSTUCTORS
#include <vulkan/vulkan_raii.hpp>


namespace fWindowSurface
{
	vk::raii::SurfaceKHR CreateWIN32(vk::raii::Instance &vulkanInstance, HWND &windowHandle);
}