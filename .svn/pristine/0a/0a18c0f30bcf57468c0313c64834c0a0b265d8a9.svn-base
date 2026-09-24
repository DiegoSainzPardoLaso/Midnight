#pragma once

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include <iostream>
#include <vector>

namespace fExtensions
{
	std::vector<const char *> CheckNeededExtensionsAvailabilityAndRetrieveThem(vk::raii::Context &vulkanContext, std::vector<const char *> &extensions, bool enableValidationLayers);
}