#include "Pools.h"

vk::raii::DescriptorPool fPool::create_descriptor_pool(const vk::raii::Device &logical_device, const uint32_t descriptor_pool_size)
{
    vk::DescriptorPoolSize pool_size(vk::DescriptorType::eUniformBuffer, descriptor_pool_size);
	
    vk::DescriptorPoolCreateInfo create_info{};
    create_info.flags         = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;
    create_info.maxSets       = descriptor_pool_size;
    create_info.poolSizeCount = 1;
    create_info.pPoolSizes    = &pool_size;


    return vk::raii::DescriptorPool(logical_device, create_info, nullptr);
}

vk::raii::CommandPool fPool::create_command_pool(const vk::raii::Device &logical_device, const uint32_t queue_family_index)
{
    vk::CommandPoolCreateInfo create_info;
    create_info.flags            = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
    create_info.queueFamilyIndex = queue_family_index;

    return vk::raii::CommandPool(logical_device, create_info, nullptr);
}
