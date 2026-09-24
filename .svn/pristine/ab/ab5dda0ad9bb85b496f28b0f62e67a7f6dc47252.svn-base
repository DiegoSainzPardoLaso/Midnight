#include "Queue.h"

Queue fQueue::create(const vk::raii::Device &logical_device, const vk::DeviceQueueCreateInfo &queue_info)
{
	return
	{
		.queue = vk::raii::Queue(logical_device, queue_info.queueFamilyIndex, 0),
		.index = queue_info.queueFamilyIndex
	};
}

vk::DeviceQueueCreateInfo fQueue::get_device_queue_create_info(const vk::raii::PhysicalDevice &physical_device, const vk::raii::SurfaceKHR &window_surface, const vk::QueueFlags &required_queue_flags, const vk::QueueFlags &excluding_queue_flags)
{
	std::vector<vk::QueueFamilyProperties> queue_family_properties = physical_device.getQueueFamilyProperties();

	uint32_t				  queue_family_index = 0;
	vk::QueueFamilyProperties family_properties;

	for (uint32_t q_fam_idx = 0; q_fam_idx < queue_family_properties.size(); q_fam_idx++)
	{
		if (queue_family_properties[q_fam_idx].queueFlags & required_queue_flags && !(queue_family_properties[q_fam_idx].queueFlags & excluding_queue_flags) && physical_device.getSurfaceSupportKHR(q_fam_idx, *window_surface))
		{
			queue_family_index = q_fam_idx;
			family_properties  = queue_family_properties[q_fam_idx];
		}		
	}

	if (queue_family_index == ~0)
	{
		std::cerr << "[ERORR] - Function Name: CREATE_LOGICAL_DEVICE_AND_QUEUES - Could Not find a queue for Graphics\n";
		abort();
	}

	float queue_family_priority = 1.0f;
	
	vk::DeviceQueueCreateInfo create_info;	
	create_info.queueFamilyIndex = queue_family_index;
	create_info.queueCount		 = 1;
	create_info.pQueuePriorities = &queue_family_priority;
	
	return create_info;
}

vk::DeviceQueueCreateInfo fQueue::get_device_queue_create_info(const vk::raii::PhysicalDevice &physical_device, const vk::raii::SurfaceKHR &window_surface, const vk::QueueFlags &required_queue_flags)
{
	std::vector<vk::QueueFamilyProperties> queue_family_properties = physical_device.getQueueFamilyProperties();

	uint32_t				  queue_family_index = 0;
	vk::QueueFamilyProperties family_properties;

	for (uint32_t q_fam_idx = 0; q_fam_idx < queue_family_properties.size(); q_fam_idx++)
	{
		if (queue_family_properties[q_fam_idx].queueFlags & required_queue_flags && physical_device.getSurfaceSupportKHR(q_fam_idx, *window_surface))
		{
			queue_family_index = q_fam_idx;
			family_properties  = queue_family_properties[q_fam_idx];
		}		
	}

	if (queue_family_index == ~0)
	{
		std::cerr << "[ERORR] - Function Name: CREATE_LOGICAL_DEVICE_AND_QUEUES - Could Not find a queue for Graphics\n";
		abort();
	}

	float queue_family_priority = 1.0f;
	
	vk::DeviceQueueCreateInfo create_info;	
	create_info.queueFamilyIndex = queue_family_index;
	create_info.queueCount		 = 1;
	create_info.pQueuePriorities = &queue_family_priority;
	
	return create_info;
}