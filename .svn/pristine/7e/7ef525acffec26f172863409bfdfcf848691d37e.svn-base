// #include "UniformBuffer.h"
/*
UniformBufferObjectMVP fUniformBuffer::CreateMVP(vk::raii::PhysicalDevice &physicalDevice, vk::raii::Device &logicalDevice)
{
    uint32_t sizeOf   = sizeof(Mat4) * 3;
    Mat4     identity = Identity();

    return
    {
        .model  = identity,
        .view   = identity,
        .proj   = identity,
        .sizeOf = sizeOf,
        .buffer = {nullptr, nullptr, nullptr}
        //.buffer = fBuffer::Create
        //(
        //    physicalDevice,
        //    logicalDevice,
        //    sizeOf,            
        //    vk::BufferUsageFlagBits::eUniformBuffer,
        //    vk::SharingMode::eExclusive,
        //    vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible
        //)
    };
}



UniformBufferObjectMVP fUniformBuffer::CreateMVP(vk::raii::PhysicalDevice &physicalDevice, vk::raii::Device &logicalDevice, Mat4 &model, Mat4 &view, Mat4 &projection)
{
    uint32_t sizeOf = sizeof(Mat4) * 3;

    return
    {
        .model  = model,
        .view   = view,
        .proj   = projection,
        .sizeOf = sizeOf,
        .buffer = {nullptr, nullptr, nullptr}
        // .buffer = fBuffer::Create
        // (
        //     physicalDevice,
        //     logicalDevice,
        //     sizeOf,
        //     vk::BufferUsageFlagBits::eUniformBuffer,
        //     vk::SharingMode::eExclusive,
        //     vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible
        // )        
    };
}


void fUniformBuffer::UpdateMVPAndCopyMemory(UniformBufferObjectMVP &ubo, Mat4 &model, Mat4 &view, Mat4 &projection)
{
    projection.data[5] = projection[5] * -1;
        
    ubo.model = model;
    ubo.view  = view;
    ubo.proj  = projection;
    
    memcpy(ubo.buffer.memoryMap, &ubo, ubo.sizeOf);
}
*/