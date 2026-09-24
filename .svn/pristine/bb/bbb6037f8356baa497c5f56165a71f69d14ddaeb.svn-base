#include "VulkanImage.h"


Image_VK fImage::Create(vk::raii::PhysicalDevice &physicalDevice, vk::raii::Device &logicalDevice, uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::ImageAspectFlagBits aspectFlags)
{
	Image_VK i;

	//======================================================================//
	// Image
	//======================================================================//
	vk::ImageCreateInfo imageInfo
	{
		.imageType     = vk::ImageType::e2D,
		.format        = format,
		.extent        = {width, height, 1},
		.mipLevels     = 1,
		.arrayLayers   = 1,
		.samples       = vk::SampleCountFlagBits::e1,
		.tiling        = tiling,
		.usage		   = usage,
		.sharingMode   = vk::SharingMode::eExclusive,
		.initialLayout = vk::ImageLayout::eUndefined 
	};

	i.image = vk::raii::Image(logicalDevice, imageInfo);

	vk::MemoryRequirements memRequirements = i.image.getMemoryRequirements();
	vk::MemoryAllocateInfo allocInfo
	{
		.allocationSize = memRequirements.size,
		.memoryTypeIndex = fMemory::FindMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties) 
	};

	i.memory = vk::raii::DeviceMemory(logicalDevice, allocInfo);
	i.image.bindMemory(i.memory, 0);

	//======================================================================//
	// Image View
	//======================================================================//
	i.imageView = fImageView::Create(logicalDevice, i.image, format, aspectFlags);

	return i;	
}


void fImageView::Create(const vk::raii::Device &logicalDevice, std::vector<vk::raii::ImageView> &imageViews, const std::vector<vk::Image> &images, const vk::Format &format, const vk::ImageAspectFlags aspectFlags)
{
	assert(imageViews.empty());

	vk::ImageViewCreateInfo imageViewCreateInfo
	{
		.viewType		  = vk::ImageViewType::e2D,
		.format			  = format,
		.subresourceRange = { aspectFlags, 0, 1, 0, 1 }
	};

	for (const vk::Image &image : images)
	{
		imageViewCreateInfo.image = image;
		imageViews.emplace_back(logicalDevice, imageViewCreateInfo);
	}
}

vk::raii::ImageView fImageView::Create(vk::raii::Device &logicalDevice, vk::Image image, vk::Format &format, vk::ImageAspectFlagBits aspectFlags)
{
	vk::ImageViewCreateInfo imageViewCreateInfo
	{
		.image			  = image,
		.viewType		  = vk::ImageViewType::e2D,
		.format			  = format,
		.subresourceRange = { aspectFlags, 0, 1, 0, 1 }
	};
	 

	return vk::raii::ImageView(logicalDevice, imageViewCreateInfo);
}

