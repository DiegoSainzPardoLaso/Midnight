#include "VulkanPipeline.h"


const char *fPipeline_VK::Internal::ShaderStageName(vk::ShaderStageFlagBits shader_stage)
{
	switch (shader_stage)
	{
		case vk::ShaderStageFlagBits::eVertex:   { return VERTEX_SHADER_ENTRY_POINT_NAME;   } break;
		case vk::ShaderStageFlagBits::eFragment: { return FRAGMENT_SHADER_ENTRY_POINT_NAME; } break;
	}
}


Pipeline_VK fPipeline_VK::Create(const vk::raii::Device &logicalDevice, const RENDERING_MODE renderingMode, const VERTEX_TYPE vertexType, const vk::raii::ShaderModule &shaderModule, const vk::ShaderStageFlagBits *shaderStages, const uint32_t shaderStagesCount, const vk::raii::DescriptorSetLayout &descriptorSetLayout, const vk::Format colorFormat, const vk::Format depthFormat)
{
	Pipeline_VK pipeline;

	// =============================================================================//
	// 1. Find Entry Points 
	// =============================================================================//
	std::vector<vk::PipelineShaderStageCreateInfo> stages{};
	for (size_t entryPointIdx = 0; entryPointIdx < shaderStagesCount; entryPointIdx++)
	{
		stages.emplace_back
		(
			vk::PipelineShaderStageCreateInfo
			{
				.stage  = shaderStages[entryPointIdx],
				.module = shaderModule,
				.pName  = Internal::ShaderStageName(shaderStages[entryPointIdx])
			}
		);
	}
	
	// ================================================================================ // 	
	// 2. Dynamic state.This will cause the configuration of these values to be ignored, 
	// and I'll be able to specify the data at drawing time
	// ================================================================================ // 	
	std::vector <vk::DynamicState> dynamicStates =
	{
		vk::DynamicState::eViewport,
		vk::DynamicState::eScissor
	};

	vk::PipelineDynamicStateCreateInfo dynamicState
	{
		.dynamicStateCount = (uint32_t)(dynamicStates.size()),
		.pDynamicStates    = dynamicStates.data()
	};
	
	vk::PipelineViewportStateCreateInfo viewportState{ .viewportCount = 1, .scissorCount = 1 };	 // @note Making the viewport and scissors dynamic


	// ================================================================================ //
	// 3. Vertex Description
	// ================================================================================ //
	vk::VertexInputBindingDescription				 bindingDescription				  = fVertex_VK::GetBindingDescription(vertexType);
	std::vector<vk::VertexInputAttributeDescription> vertexInputAttributeDescriptions = fVertex_VK::GetVertexAttributeDescriptions(vertexType);
	
	vk::PipelineVertexInputStateCreateInfo vertexInputInfo
	{
		.vertexBindingDescriptionCount   = 1,
		.pVertexBindingDescriptions      = &bindingDescription,
		.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size()),
		.pVertexAttributeDescriptions    = vertexInputAttributeDescriptions.data()
	};


	// ================================================================================ //
	// 4. Setup the rasterizer
	// ================================================================================ //
	vk::PipelineInputAssemblyStateCreateInfo inputAssembly
	{
		.topology = vk::PrimitiveTopology::eTriangleList 		
	};


	vk::PolygonMode pMode = vk::PolygonMode::eFill;
	if		(renderingMode == LINE_MODE)  { pMode = vk::PolygonMode::eLine;  }
	else if (renderingMode == POINT_MODE) { pMode = vk::PolygonMode::ePoint; }


	vk::PipelineRasterizationStateCreateInfo rasterizer
	{
		.depthClampEnable		 = vk::False,
		.rasterizerDiscardEnable = vk::False,
		.polygonMode			 = pMode,
		.cullMode				 = vk::CullModeFlagBits::eNone, // @note Culling
		.frontFace				 = vk::FrontFace::eClockwise,
		.depthBiasEnable		 = vk::False,
		.lineWidth				 = 1.0f							// @note Any line thicker than 1, needs the widelines gpu feature enabled
	};

	// ================================================================================ //
	// 5. Config
	// ================================================================================ //
	
	vk::PipelineColorBlendAttachmentState colorBlendAttachment
	{
		.blendEnable		 = vk::True,
		.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha,
		.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha,
		.colorBlendOp		 = vk::BlendOp::eAdd,
		.srcAlphaBlendFactor = vk::BlendFactor::eSrcAlpha,
		.dstAlphaBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha,
		.alphaBlendOp		 = vk::BlendOp::eAdd,
		.colorWriteMask		 = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA,
	};

	vk::PipelineMultisampleStateCreateInfo multisampling
	{
		.rasterizationSamples = vk::SampleCountFlagBits::e1,
		.sampleShadingEnable  = vk::False
	};

	// vk::PipelineColorBlendAttachmentState colorBlendAttachment
	// {
	// 	.blendEnable    = vk::False,
	// 	.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA,
	// };

	vk::PipelineColorBlendStateCreateInfo colorBlending
	{
		.logicOpEnable   = vk::False,
		.logicOp		 = vk::LogicOp::eCopy,
		.attachmentCount = 1,
		.pAttachments	 = &colorBlendAttachment
	};

	// ================================================================================ //
	// 6. Create Pipeline Layout
	// ================================================================================ //

	vk::PushConstantRange pushConstantRange
	{
		.stageFlags = vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eFragment,
		.offset     = 0,
		.size		= 128 // bytes. @note that 128 bytes is the minimum size that Vulkan is able to guarantee (It can be more than this, but each physical device is different, so I use the shared minimum between all devices)
	};		

	vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo =
	{
		.setLayoutCount			= 1,
		.pSetLayouts	        = &*descriptorSetLayout,
		.pushConstantRangeCount = 1,
		.pPushConstantRanges    = &pushConstantRange,
	};

	pipeline.layout = vk::raii::PipelineLayout(logicalDevice, pipelineLayoutCreateInfo);	

	// ================================================================================ //
	// 7. Create Pipeline
	// ================================================================================ //

	vk::PipelineDepthStencilStateCreateInfo depthStencil
	{
		.depthTestEnable       = vk::True,
		.depthWriteEnable      = vk::True,
		.depthCompareOp		   = vk::CompareOp::eLess,
		.depthBoundsTestEnable = vk::False,
		.stencilTestEnable	   = vk::False
	};


	vk::StructureChain<vk::GraphicsPipelineCreateInfo, vk::PipelineRenderingCreateInfo> pipelineCreateInfoChain
	{
		vk::GraphicsPipelineCreateInfo
		{
			.stageCount			 = (uint32_t)stages.size(),
			.pStages			 = stages.data(),
			.pVertexInputState   = &vertexInputInfo,
			.pInputAssemblyState = &inputAssembly,
			.pViewportState		 = &viewportState,
			.pRasterizationState = &rasterizer,
			.pMultisampleState   = &multisampling,
			.pDepthStencilState  = &depthStencil,
			.pColorBlendState    = &colorBlending,
			.pDynamicState		 = &dynamicState,
			.layout				 = pipeline.layout,
			.renderPass			 = nullptr
		},

		vk::PipelineRenderingCreateInfo
		{
			.colorAttachmentCount    = 1,
			.pColorAttachmentFormats = &colorFormat,
			.depthAttachmentFormat   = depthFormat
		}
	};
	
	pipeline.pipeline = vk::raii::Pipeline(logicalDevice, nullptr, pipelineCreateInfoChain.get<vk::GraphicsPipelineCreateInfo>());

	return pipeline;
}
