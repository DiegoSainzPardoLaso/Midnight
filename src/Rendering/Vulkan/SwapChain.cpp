#include "SwapChain.h"

 
Swap_Chain::Swap_Chain(const vk::raii::PhysicalDevice &physical_device, const vk::raii::Device &logical_device, const vk::raii::SurfaceKHR &window_surface, const vk::PresentModeKHR present_mode, const Vec2 &dimensions)
{	
	uint32_t						  minImageCount			= 0;
	vk::PresentModeKHR				  presentationMode		= vk::PresentModeKHR::eFifo;
	auto							  surfaceCapabilities   = physical_device.getSurfaceCapabilitiesKHR(*window_surface);
	std::vector<vk::SurfaceFormatKHR> availableFormats      = physical_device.getSurfaceFormatsKHR(window_surface);
	std::vector<vk::PresentModeKHR>   availablePresentModes = physical_device.getSurfacePresentModesKHR(window_surface);

	// ================================================================================ // 
	// Surface Format
	// ================================================================================ // 
	if (availableFormats.empty())
	{
		std::cerr << "[ERROR] - Function Name: CREATE_SWAP_CHAIN - [Your graphics Card doesn't support any Surface Formats (Color Depth)]\n";
		abort();
	}

	for (auto format : availableFormats)
	{
		if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
		{
			this->surface_format = format;
			break;
		}
	}

	// ================================================================================ // 
	// Presentation Mode
	// ================================================================================ // 	

	for (vk::PresentModeKHR &pMode : availablePresentModes)
	{
		if (pMode == present_mode)
		{
			presentationMode = present_mode;
			break;
		}
	}

	if (presentationMode != present_mode)
	{
		std::cout << "[INFO] - Function Name: <CREATE_SWAP_CHAIN> - [This GPU doesn't support the desired present mode. Setting eFifo mode to default]\n"; 
	}

	// ================================================================================ // 
	// Surface Capabilities (Extent/Swap chain images dimensions)
	// ================================================================================ // 	
	if (surfaceCapabilities.currentExtent.width != UINT32_MAX)
	{
		this->extent = surfaceCapabilities.currentExtent;
	}
	else
	{
		this->extent.width  = std::clamp<uint32_t>((uint32_t)dimensions.width,  surfaceCapabilities.minImageExtent.width,  surfaceCapabilities.maxImageExtent.width);
		this->extent.height = std::clamp<uint32_t>((uint32_t)dimensions.height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
	}


	// ================================================================================ // 
	// Min Images
	// ================================================================================ // 	

	minImageCount = max(MAX_FRAMES_IN_FLIGHT, surfaceCapabilities.minImageCount);

	if ((0 < surfaceCapabilities.maxImageCount) && surfaceCapabilities.maxImageCount < minImageCount)
	{
		minImageCount = surfaceCapabilities.minImageCount;
	}

	// ================================================================================ // 	
	// Creation
	// ================================================================================ // 	
		
	vk::SwapchainCreateInfoKHR createInfo =
	{	
		.surface	      = window_surface,
		.minImageCount    = minImageCount,
		.imageFormat      = this->surface_format.format,
		.imageColorSpace  = this->surface_format.colorSpace,
		.imageExtent	  = this->extent,
		.imageArrayLayers = 1,
		.imageUsage		  = vk::ImageUsageFlagBits::eColorAttachment,
		.imageSharingMode = vk::SharingMode::eExclusive,
		.preTransform	  = surfaceCapabilities.currentTransform,
		.compositeAlpha   = vk::CompositeAlphaFlagBitsKHR::eOpaque,
		.presentMode	  = presentationMode,
		.clipped		  = true,
		
	};


	this->swap_chain = vk::raii::SwapchainKHR(logical_device, createInfo);
	this->images     = this->swap_chain.getImages();
		
	 
	fImageView::Create(logical_device, this->image_views, this->images, this->surface_format.format, vk::ImageAspectFlagBits::eColor);
}

void Swap_Chain::recreate(const vk::raii::PhysicalDevice &physical_device, const vk::raii::Device &logical_device, const vk::raii::SurfaceKHR &window_surface, const vk::PresentModeKHR present_mode, const Vec2 &window_dimensions)
{
	logical_device.waitIdle();
	clear();
	internal_create(physical_device, logical_device, window_surface, present_mode, window_dimensions);
}

void Swap_Chain::clear()
{
	for (vk::raii::ImageView &image_view : this->image_views) { image_view.clear(); }
	this->image_views.clear();
	this->swap_chain.clear();
	this->images.clear();
}

void Swap_Chain::internal_create(const vk::raii::PhysicalDevice &physical_device, const vk::raii::Device &logical_device, const vk::raii::SurfaceKHR &window_surface, const vk::PresentModeKHR present_mode, const Vec2 &window_dimensions)
{
	uint32_t						  minImageCount			= 0;
	vk::PresentModeKHR				  presentationMode		= vk::PresentModeKHR::eFifo;
	auto							  surfaceCapabilities   = physical_device.getSurfaceCapabilitiesKHR(*window_surface);
	std::vector<vk::SurfaceFormatKHR> availableFormats      = physical_device.getSurfaceFormatsKHR(window_surface);
	std::vector<vk::PresentModeKHR>   availablePresentModes = physical_device.getSurfacePresentModesKHR(window_surface);

	// ================================================================================ // 
	// Surface Format
	// ================================================================================ // 
	if (availableFormats.empty())
	{
		std::cerr << "[ERROR] - Function Name: CREATE_SWAP_CHAIN - [Your graphics Card doesn't support any Surface Formats (Color Depth)]\n";
		abort();
	}

	for (auto format : availableFormats)
	{
		if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
		{
			this->surface_format = format;
			break;
		}
	}

	// ================================================================================ // 
	// Presentation Mode
	// ================================================================================ // 	

	for (vk::PresentModeKHR &pMode : availablePresentModes)
	{
		if (pMode == present_mode)
		{
			presentationMode = present_mode;
			break;
		}
	}

	if (presentationMode != present_mode)
	{
		std::cout << "[INFO] - Function Name: <CREATE_SWAP_CHAIN> - [This GPU doesn't support the desired present mode. Setting eFifo mode to default]\n"; 
	}

	// ================================================================================ // 
	// Surface Capabilities (Extent/Swap chain images dimensions)
	// ================================================================================ // 	
	if (surfaceCapabilities.currentExtent.width != UINT32_MAX)
	{
		this->extent = surfaceCapabilities.currentExtent;
	}
	else
	{
		this->extent.width  = std::clamp<uint32_t>((uint32_t)window_dimensions.width,  surfaceCapabilities.minImageExtent.width,  surfaceCapabilities.maxImageExtent.width);
		this->extent.height = std::clamp<uint32_t>((uint32_t)window_dimensions.height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
	}


	// ================================================================================ // 
	// Min Images
	// ================================================================================ // 	

	minImageCount = max(MAX_FRAMES_IN_FLIGHT, surfaceCapabilities.minImageCount);

	if ((0 < surfaceCapabilities.maxImageCount) && surfaceCapabilities.maxImageCount < minImageCount)
	{
		minImageCount = surfaceCapabilities.minImageCount;
	}

	// ================================================================================ // 	
	// Creation
	// ================================================================================ // 	
		
	vk::SwapchainCreateInfoKHR createInfo =
	{	
		.surface	      = window_surface,
		.minImageCount    = minImageCount,
		.imageFormat      = this->surface_format.format,
		.imageColorSpace  = this->surface_format.colorSpace,
		.imageExtent	  = this->extent,
		.imageArrayLayers = 1,
		.imageUsage		  = vk::ImageUsageFlagBits::eColorAttachment,
		.imageSharingMode = vk::SharingMode::eExclusive,
		.preTransform	  = surfaceCapabilities.currentTransform,
		.compositeAlpha   = vk::CompositeAlphaFlagBitsKHR::eOpaque,
		.presentMode	  = presentationMode,
		.clipped		  = true,
		
	};


	this->swap_chain = vk::raii::SwapchainKHR(logical_device, createInfo);
	this->images     = this->swap_chain.getImages();
	
	fImageView::Create(logical_device, this->image_views, this->images, this->surface_format.format, vk::ImageAspectFlagBits::eColor);
}
