#pragma once

#include "VulkanShader.h"

struct Material_VK
{
	// @note Reallistically this should be an instance of a shader instead of
	// the shaders path, because If I want to have multiple materials each one with its own shader
	// that I can't do with this approach
	//
	const char *slang_shader_path;
};

namespace fMaterial_vk
{
	Material_VK Create(vk::raii::Device &logicalDevice, const char *slangPath);
}