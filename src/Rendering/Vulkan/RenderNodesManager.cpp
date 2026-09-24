#include "RenderNodesManager.h"

#pragma region DELETE
RenderNodeSystem_VK *fRenderNodeSystem::Create
(
    const vk::raii::PhysicalDevice                 &physicalDevice, 
	const vk::raii::Device		                   &logicalDevice, 
	const vk::raii::CommandPool	                   &commandPool, 
	const vk::raii::Queue			               &transferQueue, 
	const std::vector<uint32_t>	                   &familyQueueIndices,

    const vk::raii::DescriptorPool                 &descriptorPool,
    const vk::raii::DescriptorSetLayout            &descriptorSetLayout,

	CameraSystem		                          *&camera_system
)
{
    RenderNodeSystem_VK *manager = new RenderNodeSystem_VK();

    //==============================================================================//
    // Cameras
    //==============================================================================//

    for (unsigned int i = 0; i < camera_system->cameraCount; i++)
    {
        StaticMesh &mesh = camera_system->cameras[i].mesh;

        sRenderNode cameraNode
        {
            .mesh          = &mesh,
            .material      = nullptr,
            .transform     = &camera_system->cameras[i].transform,

            .vertexBuffer  = fBuffer::CreateVertexBuffer(physicalDevice, logicalDevice, commandPool, transferQueue, familyQueueIndices, mesh.vertices, mesh.total_vertices_byte_size),
            .indexBuffer   = fBuffer::CreateIndexBuffer (physicalDevice, logicalDevice, commandPool, transferQueue, familyQueueIndices, mesh.indices,  mesh.index_count),

            .descriptorSet = { },
            .uniformBuffer = { }
        };


        for (unsigned int uboIDX = 0; uboIDX < MAX_FRAMES_IN_FLIGHT; uboIDX++)
        {            
            cameraNode.uniformBuffer.emplace_back(fBuffer::Create(physicalDevice, logicalDevice, familyQueueIndices, sizeof(ModelViewProjectionUBO), vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible));
        }

        cameraNode.descriptorSet = fDescriptor::CreateDescriptorSets(logicalDevice, descriptorPool, MAX_FRAMES_IN_FLIGHT, descriptorSetLayout, cameraNode.uniformBuffer, { sizeof(ModelViewProjectionUBO) });            


        manager->cameraRenderNodes.emplace_back(std::move(cameraNode));
    }    

    //==============================================================================//
    // Other stuff...
    //==============================================================================//



    return manager;
}



void fRenderNodeSystem::Draw(sRenderNode &node, vk::raii::CommandBuffer &commandBuffer, vk::raii::Pipeline &pipeline, vk::raii::PipelineLayout &pipelineLayout, uint32_t currentFrameIdx)
{
    // vk::ArrayProxy<const float> values = { 0.0f };
    // commandBuffer.pushConstants(pipelineLayout, vk::ShaderStageFlagBits::eFragment, 0, values);

    commandBuffer.bindVertexBuffers(0, *node.vertexBuffer.buffer, { 0 });
    commandBuffer.bindIndexBuffer(*node.indexBuffer.buffer, 0, vk::IndexType::eUint32);

    commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipelineLayout, 0, *node.descriptorSet[currentFrameIdx], nullptr);
    
    commandBuffer.drawIndexed(node.mesh->index_count, 1, 0, 0, 0);
}




void fRenderNodeSystem::Clear(RenderNodeSystem_VK *&renderNodes)
{
    for (sRenderNode &camera : renderNodes->cameraRenderNodes)
    {   
        camera.vertexBuffer.buffer.clear();
        camera.indexBuffer.buffer.clear();
        
        for (Buffer &ubo : camera.uniformBuffer)                   { ubo.buffer.clear(); }
        for (vk::raii::DescriptorSet &dset : camera.descriptorSet) { dset.clear();       }

    }
}

#pragma endregion 

//
//
//
//
//
//
//
//
//
//
//
Render_Node_Agent::Render_Node_Agent(vk::raii::PhysicalDevice &physical_device, vk::raii::Device &logical_device, Queue &graphics_queue, Queue &transfer_queue, vk::raii::CommandPool &transfer_command_pool, vk::raii::DescriptorPool &descriptor_pool, vk::Format color_format, vk::Format depth_format)
{
    this->physical_device        = &physical_device;
    this->logical_device         = &logical_device;    
    this->graphics_queue         = &graphics_queue;
    this->transfer_queue         = &transfer_queue;
    this->transfer_commands_pool = &transfer_command_pool;
    this->descriptor_pool        = &descriptor_pool;

    this->color_surface_format   = color_format;
    this->depth_surface_format   = depth_format;
}

Render_Node_Agent::~Render_Node_Agent() 
{

}
//
//
//
void Render_Node_Agent::create_node(Mesh<sVertex> &mesh, Transform &transform, Material_VK &material)
{                
    std::vector<uint32_t> family_queue_indices = { this->transfer_queue->index, this->graphics_queue->index };
    Shader_Metadata metadata;
      
    if (!this->shaders.contains(material.slang_shader_path))    
    {
        this->shaders[material.slang_shader_path] = Shader_VK(*this->logical_device, material.slang_shader_path, metadata);
        Shader_VK &shader                         = this->shaders.at(material.slang_shader_path);
    
        if (!this->descriptor_set_layouts.contains(metadata.bindings_hash_to_get_descriptor_set_layout))
        {
            vk::raii::DescriptorSetLayout set_layout = fDescriptor::CreateDescriptorSetLayout(*this->logical_device, metadata.bindings);
            Pipeline_VK pipeline                     = fPipeline_VK::Create(*this->logical_device, RENDERING_MODE::FILL_MODE, metadata.input_vertex_type, shader.module, metadata.entry_points, metadata.entry_points_count, set_layout, this->color_surface_format, this->depth_surface_format);
            
            this->descriptor_set_layouts[metadata.bindings_hash_to_get_layout] = std::move(set_layout);
            this->pipelines[metadata.bindings_hash_to_get_layout]              = std::move(pipeline);
        }                
    
        shader.set_associated_pipeline(this->pipelines.at(metadata.bindings_hash_to_get_layout));
    }
    //else
    //{
    //    metadata = this->shaders.at(material.shader_slang_path).load_shader_metadata_from_PSMB_file();
    //}
    //
    //
    //Static_Render_Node node =
    //{
    //    .mesh               = &mesh,
    //    .shader             = &this->shaders.at(material.shader_slang_path),
    //    .transform          = &transform,
    //                            
    //    .vertex_buffer      = fBuffer::create_vertex_buffer(*this->physical_device, *this->logical_device, *this->transfer_commands_pool, this->transfer_queue->queue, family_queue_indices, mesh.vertices, mesh.dSize),
    //    .index_buffer       = fBuffer::create_index_buffer (*this->physical_device, *this->logical_device, *this->transfer_commands_pool, this->transfer_queue->queue, family_queue_indices, mesh.indices,  mesh.iCount),
    //    
    //    .descriptors_set    = { },
    //    .mvp_uniform_buffer = { }
    //};
    //
    //
    //for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    //{
    //    node.mvp_uniform_buffer.emplace_back(fBuffer::Create(*this->physical_device, *this->logical_device, family_queue_indices, sizeof(ModelViewProjectionUBO), vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible));
    //
    //}
    //std::vector<uint32_t> ubo_sizes = fMetadata::get_uniform_sizes_list_in_bytes(metadata);
    //node.descriptors_set = fDescriptor::create_descriptor_sets(*this->logical_device, *this->descriptor_pool, fDescriptor::create_descriptor_set_layout(*this->logical_device, metadata.bindings), node.mvp_uniform_buffer, ubo_sizes, MAX_FRAMES_IN_FLIGHT);
    //
    //
    //
    //this->static_nodes.emplace_back(std::move(node));
}

void Render_Node_Agent::update_nodes(const Mat4 &view, const Mat4 &projection, const uint32_t current_frame)
{
    update_mvp_ubos(view, projection, current_frame);
}

void Render_Node_Agent::draw_nodes(const vk::raii::CommandBuffer &command_buffer, const uint32_t current_frame_idx)
{
    for (size_t static_node_idx = 0; static_node_idx < static_nodes.size(); static_node_idx++)
    {
        static_nodes[static_node_idx].draw(command_buffer, current_frame_idx);
    }
}

void Render_Node_Agent::update_mvp_ubos(const Mat4 &view, const Mat4 &projection, const uint32_t current_frame)
{
    for (unsigned int i = 0; i < this->static_nodes.size(); i++)
    {
        Static_Render_Node &node = this->static_nodes[i];
    
        Mat4 mvp[3] =
        {
            node.transform->model,
            view,
            projection
        };
    
        memcpy(node.mvp_uniform_buffer[current_frame].memoryMap, &mvp, sizeof(mvp));
    }
}


