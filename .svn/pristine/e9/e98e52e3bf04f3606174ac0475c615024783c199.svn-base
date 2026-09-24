#include "Material_VK.h"


Material_VK fMaterial_vk::Create(vk::raii::Device &logicalDevice, const char *slangPath)
{
	Shader_Metadata metadata;	
	return Material_VK
	{
		.shader = Shader_VK(logicalDevice, slangPath, metadata),
	};	
}