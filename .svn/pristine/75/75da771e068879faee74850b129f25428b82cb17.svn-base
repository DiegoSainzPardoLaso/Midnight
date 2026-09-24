#include "Memory.h"

uint32_t fMemory::FindMemoryType(const vk::raii::PhysicalDevice &physicalDevice, const uint32_t memoryTypeBits, const vk::MemoryPropertyFlags properties)
{
	vk::PhysicalDeviceMemoryProperties memoryProperties = physicalDevice.getMemoryProperties();
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
	{
		if ((memoryTypeBits & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties)) { return i; }
	}

	std::cout << "[ERROR] - Function Name: <FindMemoryType> - Failed to find Suitable memory Type\n";
	abort();
}
