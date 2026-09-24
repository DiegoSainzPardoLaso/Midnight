#include "RenderNode.h"

void Static_Render_Node::draw(const vk::raii::CommandBuffer &command_buffer, const uint32_t current_frame_idx)
{
    command_buffer.bindVertexBuffers(0, *this->vertex_buffer.buffer, { 0 });
    command_buffer.bindIndexBuffer(*this->index_buffer.buffer, 0, vk::IndexType::eUint32);

    // command_buffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, this->shader->associated_pipeline->layout, 0, *descriptors_set[current_frame_idx], nullptr);

    command_buffer.drawIndexed(this->mesh->index_count, 1, 0, 0, 0);
}
