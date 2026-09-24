#pragma once

#include <fstream>

#define VK_USE_PLATFORM_WIN32_KHR
#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>


#include <slang/slang.h>
#include <slang/slang-com-ptr.h>
#include <slang/slang-com-helper.h>


#include "VulkanConfig.h"
#include "VulkanPipeline.h"


#include "../../File/File.h"
#include "../../Utilities/Utilities.hpp"
#include "../../Engine/EngineConfig.h"


struct Uniform
{
	vk::DescriptorType		type;
	uint32_t				size;
	uint32_t			    offset;
	vk::ShaderStageFlagBits shader_stage;
};

struct Shader_Metadata
{
	std::vector<char>                           shader_buffer;
	// VERTEX_TYPE				                    input_vertex_type;
	vk::ShaderStageFlagBits                    *entry_points;
	uint32_t				                    entry_points_count;
							                   
							                   
	Uniform									   *uniforms;	
    uint32_t				                    uniforms_count;                  
    uint32_t				                    uniform_required_buffer_size;	// @note the sum of all uniform sizes

	std::vector<vk::DescriptorSetLayoutBinding> bindings;
	uint32_t								    bindings_hash_to_get_descriptor_set_layout;
};


class Shader_VK
{
public:
	char				   path[128];
	long long			   last_write_time;
	vk::raii::ShaderModule module = nullptr;
	Pipeline_VK			  *associated_pipeline;

public:
	Shader_VK() : path(""), last_write_time(-1), module(nullptr) {};
	Shader_VK(const vk::raii::Device &logical_device, const char *slang_path, Shader_Metadata &out_metadata);   

public:	
	void update();	

public:
	void				   set_associated_pipeline(Pipeline_VK &pipeline);
	Shader_Metadata		   load_shader_metadata_from_PSMB_file();

private:
	void				   forced_recompilation();
	bool				   load_already_compiled_shader_and_get_metadata_from_its_PSMB(const vk::raii::Device &logicalDevice, const char *spirvPath, Shader_Metadata &out_metadata);	
	void				   write_shader_PSMB_to_file(const char *file_name, Shader_Metadata &metadata);
	vk::raii::ShaderModule create_shader_module(const vk::raii::Device &LOGICAL_DEVICE, std::vector<char> &shaderBuffer);
};




extern Slang::ComPtr<slang::IGlobalSession> SLANG_GLOBAL_SESSION;
namespace fSlang
{
	void initialize();
	bool compile_and_write_shader_to_file(const vk::raii::Device &logicalDevice, const char *slangPath, const char *spirvPath, Shader_Metadata &out_metadata);

	namespace Internal
	{
		std::string				get_slang_buffer(const char *path, std::vector<SlangStage> &out_slang_stages);
		Shader_Metadata         create_shader_meta_data(const vk::raii::Device &logical_device, const char *slang_path, const char *spirv_path, slang::ProgramLayout *program_layout, std::vector<const char *> &entry_points, std::vector<SlangStage> &uniform_stages);
		void					write_compiled_spirV_to_file(const char *spirv_path, char *spirv_code_buffer_pointer, uint32_t spirv_buffer_size);

		uint32_t				size_of(std::string &type);
		uint32_t				analyze_type_and_get_size(slang::TypeReflection *type);
		vk::ShaderStageFlagBits get_vulkan_shader_stage_equivalent(SlangStage slang_stage);
		vk::ShaderStageFlagBits get_vulkan_shader_stage_equivalent(const char *shader_stage_name);
		void					diagnose(slang::IBlob *diagnostics_blob);
	}
}

namespace fMetadata
{
	std::vector<uint32_t> get_uniform_sizes_list_in_bytes(const Shader_Metadata &metadata);
}