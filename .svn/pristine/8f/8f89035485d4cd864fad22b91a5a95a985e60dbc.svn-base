#pragma once

#include "VulkanConfig.h"
#include "Material_VK.h"
#include "Buffer.h"
#include "VulkanShader.h"

#include "../../Types/Mesh.h"
#include "../../Types/Transform.h"




struct Static_Render_Node
{
	Mesh<sVertex> *mesh;
	Shader_VK	  *shader;
	Transform	  *transform;

	// ==============================
	//		  Geometry Buffers
	// ==============================
	Buffer vertex_buffer;
	Buffer index_buffer;

	// ==============================
	//		 UBO's & Descriptors
	// ==============================
	std::vector<vk::raii::DescriptorSet> descriptors_set;
	std::vector<Buffer>					 mvp_uniform_buffer;


	void draw(const vk::raii::CommandBuffer &command_buffer, const uint32_t current_idx);
};




struct sRenderNode
{
	// ==============================
	//		  Object Pointers
	// ==============================
	StaticMesh  *mesh; 
	Material_VK *material;
	Transform   *transform;

	// ==============================
	//		  Geometry Buffers
	// ==============================
	Buffer vertexBuffer;
	Buffer indexBuffer;

	// ==============================
	//		 UBO's & Descriptors
	// ==============================
	std::vector<vk::raii::DescriptorSet> descriptorSet;
	std::vector<Buffer>					 uniformBuffer;
	// Buffer				    uniformBuffer[MAX_FRAMES_IN_FLIGHT];
	// vk::raii::DescriptorSet descriptorSet[MAX_FRAMES_IN_FLIGHT];
};


struct aRenderNode
{
	AnimatedMesh *mesh; 
	Material_VK  *material;
	Transform    *transform;

	Buffer		  vertexBuffer;
	Buffer		  indexBuffer;
};