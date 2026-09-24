#include "VulkanRenderer.h"

#pragma region VULKAN_STATE
 
uint32_t							 CURRENT_FRAME_INDEX	= 0;
RENDERING_MODE						 CURRENT_RENDERING_MODE = FILL_MODE;

Grid_VK								*GRID_VK				= nullptr;

// ============================================================================ // 

PFN_vkCreateInstance				 VULKAN_DLL		 = NULL;
									 
// ============================================================================ // 
#ifdef _DEBUG
	bool							 ENABLE_VALIDATION_LAYERS = true;			
#else
	bool							 ENABLE_VALIDATION_LAYERS = false;				
#endif

std::vector<const char *>			 VALIDATION_LAYERS =
									 {	
									 	 "VK_LAYER_KHRONOS_validation",
									 };
									 
std::vector<const char *>			 PHYSICAL_DEVICE_REQUIRED_EXTENSIONS =
									 {
									  	 VK_KHR_SWAPCHAIN_EXTENSION_NAME,
										 
									 };

std::vector<const char *>			 LOGICAL_DEVICE_REQUIRED_EXTENSIONS = 
									 {
										vk::KHRSwapchainExtensionName,
									 };
									 
std::vector<const char *>			 VULKAN_REQUIRED_EXTENSIONS =
									 {
										 VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
										 VK_KHR_SURFACE_EXTENSION_NAME,										 
									 	 
									 	 // @note This one should always be the last one because If validation layers are not enabled the number of extensions required will be EXTENSIONS.size() - 1 
									 	 // leaving the debug messenger out.
									 	 //
										 VK_EXT_DEBUG_UTILS_EXTENSION_NAME									 	 
									 };
									 
									 
// ============================================================================ // 
									 
vk::raii::DescriptorSetLayout        descriptorSetLayout = nullptr;
									 									 


std::vector<vk::Format>				 POSSIBLE_SUPPORTED_DEPTH_FORMATS
									 {
									      vk::Format::eD32Sfloat,             // 32 bits Depth Buffer
									      vk::Format::eD32SfloatS8Uint,       // 32 bits Depth Buffer 8 bits stencil buffer
									      vk::Format::eD24UnormS8Uint,        // 24 bits Depth Buffer 8 bits stencil buffer
									 };
vk::ImageTiling						 DEPTH_IMAGE_TILING = vk::ImageTiling::eOptimal;

// ============================================================================ // 

vk::raii::Pipeline					 SHADER_PIPELINE		= nullptr;
vk::raii::PipelineLayout			 SHADER_PIPELINE_LAYOUT = nullptr;

// ============================================================================ // 

#pragma endregion


void fVulkan::Initialize(HWND &handle, Vec2 &windowDimensions, RenderNodeSystem_VK *&renderNodesSystem, CameraSystem *&camera_system, Vulkan_Renderer *&v_renderer)
{	
	std::vector<Binding> bindings =
	{
		{ 0, vk::DescriptorType::eUniformBuffer, 1, vk::ShaderStageFlagBits::eVertex },		
	};

	descriptorSetLayout = fDescriptor::CreateDescriptorSetLayout(v_renderer->logical_device, bindings);
	

	renderNodesSystem = fRenderNodeSystem::Create
	(
		v_renderer->physical_device,
		v_renderer->logical_device,
		v_renderer->transfer_command_pool,
		v_renderer->transfer_queue.queue,
		{ v_renderer->graphics_and_presentation_queue.index, v_renderer->transfer_queue.index },
		
		v_renderer->descriptors_pool,
		descriptorSetLayout,
		
		camera_system
	);
	
	
	
	Shader_Metadata metada;
	Shader_VK shader	   = Shader_VK(v_renderer->logical_device, "C:/Midnight/shaders/slang/test.slang", metada);
	Pipeline_VK pip		   = fPipeline_VK::Create(v_renderer->logical_device, FILL_MODE, VERTEX_TYPE::STATIC_VERTEX, shader.module, metada.entry_points, metada.entry_points_count, descriptorSetLayout, v_renderer->swap_chain.surface_format.format, v_renderer->depth_buffer.format);
	SHADER_PIPELINE		   = std::move(pip.pipeline);	
	SHADER_PIPELINE_LAYOUT = std::move(pip.layout);

			
	GRID_VK = new Grid_VK(v_renderer->physical_device, v_renderer->logical_device, { v_renderer->graphics_and_presentation_queue.index, v_renderer->transfer_queue.index }, v_renderer->transfer_command_pool, v_renderer->descriptors_pool, v_renderer->transfer_queue.queue, v_renderer->swap_chain.surface_format.format, v_renderer->depth_buffer.format);
}
 

void fVulkan::Draw(RenderNodeSystem_VK *&renderableObjectsManager, Camera *&activeCamera, Vec2 &windowDimensions, Vulkan_Renderer *&v_renderer)
{
	if (windowDimensions.width == 0 ||  windowDimensions.height == 0) { return; }

	
	GRID_VK->Update(activeCamera->view, activeCamera->projection, activeCamera->transform.position, CURRENT_FRAME_INDEX);
	UpdateMVP_UBO(renderableObjectsManager, activeCamera->view, activeCamera->projection, CURRENT_FRAME_INDEX);





	auto fenceResult = v_renderer->logical_device.waitForFences(*v_renderer->draw_signal_fence[CURRENT_FRAME_INDEX], vk::True, UINT64_MAX);
	if (fenceResult != vk::Result::eSuccess)
	{
		std::cout << "[ERROR] - Function Name: <DRAW> - Failed to wait for fence\n";
		abort();
	}

	v_renderer->logical_device.resetFences(*v_renderer->draw_signal_fence[CURRENT_FRAME_INDEX]);

	// @note Structured Bindings useful to get multiple values. Is like usinga a std::tuple<> (In this case is a vk::ResultValue<uint32_t> though)
	//	
	
	auto [result, imageIndex] = v_renderer->swap_chain.swap_chain.acquireNextImage(UINT64_MAX, *v_renderer->present_complete_signal_semaphore[CURRENT_FRAME_INDEX], nullptr);
	 

	v_renderer->graphics_command_buffer[CURRENT_FRAME_INDEX].reset();

	
	fCommand_Buffers::Record
		(
			v_renderer->graphics_command_buffer[CURRENT_FRAME_INDEX],
			
			v_renderer->swap_chain.images[imageIndex],
			v_renderer->swap_chain.image_views[imageIndex],
			v_renderer->swap_chain.extent,
			
			v_renderer->depth_buffer.image.image,
			v_renderer->depth_buffer.image.imageView,
			
			SHADER_PIPELINE, 
			SHADER_PIPELINE_LAYOUT, 

			renderableObjectsManager,
			activeCamera->index,
			CURRENT_FRAME_INDEX,

			GRID_VK
		);

	v_renderer->graphics_and_presentation_queue.queue.waitIdle();


	vk::PipelineStageFlags WaitDestinationStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
	const vk::SubmitInfo submitInfo
	{
		.waitSemaphoreCount   = 1,
		.pWaitSemaphores	  = &*v_renderer->present_complete_signal_semaphore[CURRENT_FRAME_INDEX],
		.pWaitDstStageMask    = &WaitDestinationStageMask,
		.commandBufferCount   = 1,
		.pCommandBuffers      = &*v_renderer->graphics_command_buffer[CURRENT_FRAME_INDEX],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores    = &*v_renderer->render_finished_signal_semaphore[CURRENT_FRAME_INDEX]
	};

	v_renderer->graphics_and_presentation_queue.queue.submit(submitInfo, *v_renderer->draw_signal_fence[CURRENT_FRAME_INDEX]);

	const vk::PresentInfoKHR presentInfoKHR
	{
		.waitSemaphoreCount = 1,
		.pWaitSemaphores    = &*v_renderer->render_finished_signal_semaphore[CURRENT_FRAME_INDEX],
		.swapchainCount     = 1,
		.pSwapchains		= &*v_renderer->swap_chain.swap_chain,
		.pImageIndices		= &imageIndex
	};

	result = v_renderer->graphics_and_presentation_queue.queue.presentKHR(presentInfoKHR);


	switch (result)
	{
		case vk::Result::eSuccess:		     { } break;
		case vk::Result::eSuboptimalKHR:     { } break;
		case vk::Result::eErrorOutOfDateKHR: { } break;

		default: break;
	}

	CURRENT_FRAME_INDEX = (CURRENT_FRAME_INDEX + 1) % MAX_FRAMES_IN_FLIGHT;
	
 

}

 

// ================================================================================ // 

 

void UpdateMVP_UBO(RenderNodeSystem_VK *&renderNodesManager, Mat4 &view, Mat4 &projection, uint32_t currentFrame)
{			
	for (unsigned int i = 0; i < renderNodesManager->cameraRenderNodes.size(); i++)
	{
		sRenderNode &node = renderNodesManager->cameraRenderNodes[i];

		Mat4 mvp[3] =
		{
			node.transform->model,
			view,
			projection
		};

		memcpy(node.uniformBuffer[currentFrame].memoryMap, &mvp, sizeof(mvp));
	}		
}
 






const uint32_t Max_Descriptors_Per_Pool = 1024;
//
//
//
Vulkan_Renderer::Vulkan_Renderer(const HWND &window_handle, const Vec2 &window_dimensions, const Vec3 &new_background_color)
{
	load_vulkan();
	create_vulkan_instance();
	pick_physical_device();
		
	fSlang::initialize();					// @warning I should initialize slang from somewhere else...

	this->debug_messenger = fDebug_Messenger::Create(this->vulkan_instance, ENABLE_VALIDATION_LAYERS);
	create_window_surface(window_handle);
	set_up_queues_and_create_logical_device();	

	this->swap_chain			  = Swap_Chain(this->physical_device, this->logical_device, this->window_surface, vk::PresentModeKHR::eFifo, window_dimensions);
	this->depth_buffer			  = fDepth_Buffer::Create(this->physical_device, this->logical_device, this->swap_chain.extent, POSSIBLE_SUPPORTED_DEPTH_FORMATS, DEPTH_IMAGE_TILING);

	this->graphics_command_pool   = fPool::create_command_pool(this->logical_device, this->graphics_and_presentation_queue.index);
	this->transfer_command_pool   = fPool::create_command_pool(this->logical_device, this->transfer_queue.index);
	this->graphics_command_buffer = fCommand_Buffers::Create  (this->logical_device, this->graphics_command_pool, MAX_FRAMES_IN_FLIGHT);

	this->descriptors_pool		  = fPool::create_descriptor_pool(this->logical_device, Max_Descriptors_Per_Pool);

	set_up_synchronization_objects();

	this->background_color   = new_background_color;
	this->current_dimensions = window_dimensions;
	render_nodes_agent		 = new Render_Node_Agent(this->physical_device, this->logical_device, this->graphics_and_presentation_queue, this->transfer_queue, this->transfer_command_pool, this->descriptors_pool, this->swap_chain.surface_format.format, this->depth_buffer.format);
}

Vulkan_Renderer::~Vulkan_Renderer()
{
	this->logical_device.waitIdle();
	
	for (vk::raii::Semaphore &semaphore : this->present_complete_signal_semaphore) { semaphore.clear(); }
	for (vk::raii::Semaphore &semaphore : this->render_finished_signal_semaphore)  { semaphore.clear(); }
	for (vk::raii::Fence     &fence		: this->draw_signal_fence)				   { fence.clear();		}
	

	// @important fRenderNodeSystem::Clear(renderNodes);


	for (vk::raii::CommandBuffer &command : this->graphics_command_buffer) { command.clear(); }
	this->graphics_command_pool.clear();

	this->swap_chain.clear();
	this->window_surface.clear();
	this->logical_device.clear();
	this->vulkan_instance.clear();
}
//
//
//
void Vulkan_Renderer::update(const Mat4 &view, const Mat4 &projection, const Vec2 &new_window_dimensions)
{
	recreate_swap_chain_and_depth_buffer(new_window_dimensions);
	update_rendering_mode();

	// this->render_nodes_agent->update_nodes(view, projection, CURRENT_FRAME_INDEX);		
}

void Vulkan_Renderer::draw()
{
	if (this->current_dimensions.width == 0 || this->current_dimensions.height == 0) { return; }
	
	auto fence_result = this->logical_device.waitForFences(*this->draw_signal_fence[CURRENT_FRAME_INDEX], vk::True, UINT64_MAX);
	if (fence_result != vk::Result::eSuccess)
	{
		std::cout << "[ERROR] - Function Name: <DRAW> - Failed to wait for fence\n";
		abort();
	}

	logical_device.resetFences(*draw_signal_fence[CURRENT_FRAME_INDEX]);

	// @note Structured Bindings useful to get multiple values. Is like usinga a std::tuple<> (In this case is a vk::ResultValue<uint32_t> though)
	//	
	auto [result, swap_chain_image_index] = this->swap_chain.swap_chain.acquireNextImage(UINT64_MAX, *this->present_complete_signal_semaphore[CURRENT_FRAME_INDEX], nullptr);

	this->graphics_command_buffer[CURRENT_FRAME_INDEX].reset();


	// fCommand_Buffers::record_draw_command(this->graphics_command_buffer[CURRENT_FRAME_INDEX], this->swap_chain, this->depth_buffer, this->swap_chain.extent, this->background_color, CURRENT_FRAME_INDEX);
	

	//====================//
	// Presentation		  //
	//====================//
	//
	this->graphics_and_presentation_queue.queue.waitIdle();


	vk::PipelineStageFlags wait_destination_stage_mask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
	
	const vk::SubmitInfo submit_info
	{
		.waitSemaphoreCount   = 1,
		.pWaitSemaphores      = &*this->present_complete_signal_semaphore[CURRENT_FRAME_INDEX],
		.pWaitDstStageMask    = &wait_destination_stage_mask,
		.commandBufferCount   = 1,
		.pCommandBuffers	  = &*this->graphics_command_buffer[CURRENT_FRAME_INDEX],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores	  = &*this->render_finished_signal_semaphore[CURRENT_FRAME_INDEX]
	};

	graphics_and_presentation_queue.queue.submit(submit_info, *this->draw_signal_fence[CURRENT_FRAME_INDEX]);

	const vk::PresentInfoKHR presentInfoKHR
	{
		.waitSemaphoreCount = 1,
		.pWaitSemaphores    = &*this->render_finished_signal_semaphore[CURRENT_FRAME_INDEX],
		.swapchainCount     = 1,
		.pSwapchains		= &*swap_chain.swap_chain,
		.pImageIndices		= &swap_chain_image_index
	};

	result = this->graphics_and_presentation_queue.queue.presentKHR(presentInfoKHR);

	switch (result)
	{
		case vk::Result::eSuccess:			 {} break;
		case vk::Result::eSuboptimalKHR:	 {} break;
		case vk::Result::eErrorOutOfDateKHR: {} break;

		default: break;
	}

	CURRENT_FRAME_INDEX = (CURRENT_FRAME_INDEX + 1) % MAX_FRAMES_IN_FLIGHT;
}
//
//
//
void Vulkan_Renderer::load_vulkan()
{
#ifdef _WIN32
	HMODULE vulkan_module = LoadLibrary(L"vulkan-1.dll");
	if (!vulkan_module)
	{
		std::cout << "[ERROR] - Function Name <WIN32_LOAD_VULKAN> - Failed to load vulkan module(Vulkan - 1.dll is unavailable)\n";
		abort();
	}

	VULKAN_DLL = (PFN_vkCreateInstance)GetProcAddress(vulkan_module, "vkCreateInstance");

	if (!VULKAN_DLL)
	{
		std::cout << "[ERROR] - Function Name <WIN32_LOAD_VULKAN> - Failed to load vk Instance Function Pointer\n";
		abort();
	}
#endif
}

void Vulkan_Renderer::create_vulkan_instance()
{
	constexpr vk::ApplicationInfo app_info
	{
		.pApplicationName	= "Midnight engine",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName		= "Midnight engine",
		.engineVersion		= VK_MAKE_VERSION(1, 0, 0),
		.apiVersion			= vk::ApiVersion14,
	};
		
	vk::InstanceCreateInfo create_info{ .pApplicationInfo = &app_info };
	
	if (ENABLE_VALIDATION_LAYERS)
	{
		if (check_if_the_desired_validation_layers_are_available(VALIDATION_LAYERS))
		{
			create_info.enabledLayerCount   = (uint32_t)VALIDATION_LAYERS.size();
			create_info.ppEnabledLayerNames = VALIDATION_LAYERS.data();
		}
		else
		{
			std::cout << "[ERROR] - Function Name <" << "CREATE_VULKAN_INSTANCE" << "> - Result <" << 1 << "> " << " - [" << "Failed to Find Required Validation Layers" << "] \n";
			abort();	
		}
	}
	
	std::vector<const char *> extensions = check_needed_extensions_availability_and_retrieve_them(VULKAN_REQUIRED_EXTENSIONS);
	
	int size = ENABLE_VALIDATION_LAYERS ? (int)VULKAN_REQUIRED_EXTENSIONS.size() : (int)(VULKAN_REQUIRED_EXTENSIONS.size() - 1);

	// @note That i check for just less than, that's because the debug version causes renderdoc to load debug_utils ext twice
	// but there's no big deal, so just check if it's less than the required extensions and that's it
	//
	if (extensions.size() < size)
	{
		std::cout << "[Error] - Function Name: <CREATE_VULKAN_INSTANCE> - Error <1> - [Failed to retrieved all the extensions needed (Or I'm using RenderDoc)]\n";

		std::cout << "Extensions Required: \n";
		for (const char *ext : VULKAN_REQUIRED_EXTENSIONS)
		{
			std::cout << "\t" << ext << "\n";
		}

		std::cout << "Retrieved Extensions: \n";
		for (const char *ext : extensions)
		{
			std::cout << "\t" << ext << "\n";
		}

		abort();
	}

	create_info.enabledExtensionCount   = (uint32_t)extensions.size();
	create_info.ppEnabledExtensionNames = extensions.data();
	
	this->vulkan_instance = vk::raii::Instance(this->vulkan_context, create_info);
}

void Vulkan_Renderer::pick_physical_device()
{
	std::vector<vk::raii::PhysicalDevice> physical_devices = this->vulkan_instance.enumeratePhysicalDevices();

	if (physical_devices.size() <= 0)
	{
		std::cerr << "[ERROR] - Function Name: PICK_PHYSICAL_DEVICE - [Failed to Find Any Physical Device on this Machine (This computer doesn't have a Graphics Card Or Your Graphics Card Doesn't Support Vulkan)]\n";
		abort();
	}

	// @note I'm just grabbing the first GPU I find. I should Pickup the "best" one
	//
	this->physical_device = physical_devices.at(0);
	
	// ================================================================================ // 
	
	if (!(this->physical_device.getProperties().apiVersion >= vk::ApiVersion13))
	{
		std::cerr << "[ERROR] - Function Name: PICK_PHYSICAL_DEVICE - [Your Graphics Card Doesn't support Vukan 1.3 or higher]\n";
		abort();
	}

	std::vector<vk::QueueFamilyProperties> queue_families = this->physical_device.getQueueFamilyProperties();

	bool support_graphics = false;
	for (vk::QueueFamilyProperties &queue : queue_families)
	{
		if (queue.queueFlags & vk::QueueFlagBits::eGraphics) { support_graphics = true; }
	}

	if (!support_graphics)
	{
		std::cerr << "[ERROR] - Function Name: PICK_PHYSICAL_DEVICE - [Your Graphics Card Doesn't queues with support for graphics]\n";
		abort();
	}

	// ================================================================================ // 

	// @note Check for needed extensions
	//
	auto physical_device_extensions = this->physical_device.enumerateDeviceExtensionProperties();
	uint32_t supported_extensions   = 0;
	
	for (const char *ext : PHYSICAL_DEVICE_REQUIRED_EXTENSIONS)
	{
		for (auto &pdExt : physical_device_extensions)
		{
			if (strcmp(ext, pdExt.extensionName) == 0) 
			{
				supported_extensions++;
			}
		}
	}

	if (supported_extensions != PHYSICAL_DEVICE_REQUIRED_EXTENSIONS.size())
	{
		std::cerr << "[ERROR] - Function Name: PICK_PHYSICAL_DEVICE - [Your Graphics Card Doesn't support all the required extensions]\n";
		abort();
	}
}

void Vulkan_Renderer::create_window_surface(const HWND &window_handle)
{
#ifdef _WIN32
	vk::Win32SurfaceCreateInfoKHR create_info{};
	create_info.hinstance = GetModuleHandle(nullptr);
	create_info.hwnd	  = window_handle;
	this->window_surface  = this->vulkan_instance.createWin32SurfaceKHR(create_info);
#endif
}

void Vulkan_Renderer::set_up_queues_and_create_logical_device()
{
	vk::DeviceQueueCreateInfo graphics_queue_create_info = fQueue::get_device_queue_create_info(this->physical_device, window_surface, vk::QueueFlagBits::eGraphics);
	vk::DeviceQueueCreateInfo transfer_queue_create_info = fQueue::get_device_queue_create_info(this->physical_device, window_surface, vk::QueueFlagBits::eTransfer, vk::QueueFlagBits::eGraphics);	
	//
	// 
	//
	std::vector<vk::DeviceQueueCreateInfo> queue_create_infos =
	{
		graphics_queue_create_info,
		transfer_queue_create_info
	};

	vk::StructureChain<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan11Features, vk::PhysicalDeviceVulkan13Features, vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT> featureChain =
	{
		{
			.features = {.fillModeNonSolid = true }
		},
		// 11
		{
			.shaderDrawParameters = true,
		},
		// 13
		{
			.synchronization2 = true,
			.dynamicRendering = true,   // Gets rid of the necesity of framebuffers and render passes
		},
		// Dynamic State
		{
			.extendedDynamicState = true,
		},
	};

	vk::DeviceCreateInfo logical_device_create_info
	{
		.pNext				     = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
		.queueCreateInfoCount    = (uint32_t)queue_create_infos.size(),
		.pQueueCreateInfos	     = queue_create_infos.data(),
		.enabledExtensionCount   = static_cast<uint32_t>(LOGICAL_DEVICE_REQUIRED_EXTENSIONS.size()),
		.ppEnabledExtensionNames = LOGICAL_DEVICE_REQUIRED_EXTENSIONS.data()
	};

	this->logical_device = vk::raii::Device(this->physical_device, logical_device_create_info);
	//
	//=======================//
	//
	this->graphics_and_presentation_queue = fQueue::create(this->logical_device, graphics_queue_create_info);
	this->transfer_queue				  = fQueue::create(this->logical_device, transfer_queue_create_info);

}

void Vulkan_Renderer::set_up_synchronization_objects()
{
	assert(this->present_complete_signal_semaphore.empty() && this->render_finished_signal_semaphore.empty() && this->draw_signal_fence.empty());

	for (size_t i = 0; i < this->swap_chain.images.size(); i++)
	{
		this->render_finished_signal_semaphore.emplace_back(this->logical_device, vk::SemaphoreCreateInfo());
	}

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
	{
		this->present_complete_signal_semaphore.emplace_back(vk::raii::Semaphore(this->logical_device , vk::SemaphoreCreateInfo()));
		this->draw_signal_fence.emplace_back(vk::raii::Fence(this->logical_device, { .flags = vk::FenceCreateFlagBits::eSignaled }));
	}
}

bool Vulkan_Renderer::check_if_the_desired_validation_layers_are_available(std::vector<const char *> validation_layers)
{
	uint32_t found_layers_count = 0;
	std::vector<vk::LayerProperties> layer_properties = this->vulkan_context.enumerateInstanceLayerProperties();

	assert(layer_properties.size() != 0, "Failed to find any layers in your system");

	for (const char *wantedLayer : validation_layers)
	{
		for (vk::LayerProperties &layer_property : layer_properties)
		{
			if (strcmp(wantedLayer, layer_property.layerName) == 0)
			{
				found_layers_count++;
			}
		}
	}

	if (found_layers_count == validation_layers.size()) { return true;  }

	return false;
}

std::vector<const char *> Vulkan_Renderer::check_needed_extensions_availability_and_retrieve_them(std::vector<const char *> &extensions)
{
	std::vector<const char *> required_extensions{};
	std::vector<vk::ExtensionProperties> retrievedExtensions = this->vulkan_context.enumerateInstanceExtensionProperties();

	unsigned int uniforms_count = ENABLE_VALIDATION_LAYERS ? extensions.size() : extensions.size() - 1;

	for (unsigned int i = 0; i < uniforms_count; i++)
	{
		for (vk::ExtensionProperties &extension : retrievedExtensions)
		{
			if (strcmp(extensions.at(i), extension.extensionName) == 0)
			{
				required_extensions.emplace_back(extensions.at(i));
			}
		}

	}

	return required_extensions;
}
//
//
//
void Vulkan_Renderer::recreate_swap_chain_and_depth_buffer(const Vec2 &window_dimensions)
{
	bool recreate_swap_chain = this->current_dimensions == window_dimensions ? false : true;
	this->current_dimensions = window_dimensions;

	if (recreate_swap_chain && (window_dimensions.width != 0 || window_dimensions.height != 0))
	{
		swap_chain.recreate(this->physical_device, this->logical_device, this->window_surface, vk::PresentModeKHR::eFifo, window_dimensions);
		fDepth_Buffer::Recreate(this->physical_device, this->logical_device, this->depth_buffer, this->swap_chain.extent, vk::ImageTiling::eOptimal);
	}
}

void Vulkan_Renderer::update_rendering_mode()
{
	if (Input::Key_Left_Shift && fInput::FirstPress(KEY_1) && this->current_rendering_mode != FILL_MODE)
	{
		this->logical_device.waitIdle();

		// Recreate All Shader Pipelines to be LINE_MODE
		
		this->current_rendering_mode = FILL_MODE;
	}

	if (Input::Key_Left_Shift && fInput::FirstPress(KEY_2) && this->current_rendering_mode != LINE_MODE)
	{
		this->logical_device.waitIdle();

		// Recreate All Shader Pipelines to be LINE_MODE

		this->current_rendering_mode = LINE_MODE;
	}
}
