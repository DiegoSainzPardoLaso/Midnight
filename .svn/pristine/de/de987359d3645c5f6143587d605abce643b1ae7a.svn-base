#language slang 2026

struct model_view_projection_ubo
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

struct vertex_input
{
    float3 position;    
};

struct vertex_output
{
    float4 sv_position : SV_Position;
};


ConstantBuffer<model_view_projection_ubo> mvp_ubo;

[shader("vertex")]
vertex_output Vertex_Main(vertex_input v)
{
    vertex_output out;
    out.sv_position = mul(mvp_ubo.projection, mul(mvp_ubo.view, mul(mvp_ubo.model, float4(v.position, 1.0))));    
    return out;
}

// ====================================================================== //

struct picker_ubo
{
    int type;
    int index;
};


[SpecializationConstant] const int object_type;
[SpecializationConstant] const int object_idx;

ConstantBuffer<picker_ubo> pick_ubo;

[shader("fragment")]
float4 Fragment_Main(vertex_output v)
{
    return float4(pick_ubo.type, pick_ubo.index, 0, 0);
}    