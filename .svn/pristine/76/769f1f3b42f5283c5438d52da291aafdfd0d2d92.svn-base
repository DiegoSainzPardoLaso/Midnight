#pragma once

#include <iostream>

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

namespace fDebug_Messenger
{
	vk::DebugUtilsMessengerEXT				Create(vk::raii::Instance &vulkanInstance, bool enableValidationLayers);
	static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, vk::DebugUtilsMessageTypeFlagsEXT messageType, const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData);
}