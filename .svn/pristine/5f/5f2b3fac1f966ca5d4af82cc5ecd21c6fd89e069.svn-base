#include "Extensions.h"

std::vector<const char *> fExtensions::CheckNeededExtensionsAvailabilityAndRetrieveThem(vk::raii::Context &vulkanContext, std::vector<const char *> &extensions, bool enablevalidationLayers)
{
	std::vector<const char *> requiredExtensions{};
	std::vector<vk::ExtensionProperties> retrievedExtensions = vulkanContext.enumerateInstanceExtensionProperties();

	unsigned int uniformCount = enablevalidationLayers ? extensions.size() : extensions.size() - 1;

	for (unsigned int i = 0; i < uniformCount; i++)
	{
		for (vk::ExtensionProperties &extension : retrievedExtensions)
		{
			if (strcmp(extensions.at(i), extension.extensionName) == 0)
			{
				requiredExtensions.emplace_back(extensions.at(i));
			}
		}
		
	}

	return requiredExtensions;
}