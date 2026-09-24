#language slang 2026
// =========================================================================== //
// VERTEX SHADER
// =========================================================================== //

struct model_view_projection_ubo
{
    float4x4 model;
    float4x4 view;
    float4x4 proj;
};

struct VertexInput
{
    float3 position;
    float3 color;
    float3 normal;
    float2 uv;
}; 



struct global_shader_push_constants
{
    // The guaranteed minimum push contants size that Vulkan can provide is 128 bytes
    // So 128 / 4 bytes for each float let us with 32 unique values per shader...
    // And I have to split that into the different shader stages...
    //
    float constants[32];
};

// =========================================================================== //
// Output
// =========================================================================== //
struct VertexOutput
{
    float4 sv_position : SV_Position;
    float3 wc_position;
    float3 color;
    float3 normal;
    float2 uv;    
};

// =========================================================================== //
// Bindings
// =========================================================================== //
// The order is specified in the Create Descriptor set layout
//
//
ConstantBuffer<model_view_projection_ubo> ubo;    // 0  s

[push_constant]
ConstantBuffer<global_shader_push_constants> push_constants;


// =========================================================================== //
// uint vid : SV_VertexID

[shader("vertex")]
VertexOutput Vertex_Main(VertexInput input_vertex)
{
    VertexOutput output_vertex;        
    output_vertex.sv_position = mul(ubo.proj, mul(ubo.view, mul(ubo.model, float4(input_vertex.position, 1.0))));
    output_vertex.wc_position = input_vertex.position;
    output_vertex.color       = input_vertex.color;
    output_vertex.normal      = mul(float4(input_vertex.normal, 1.0), ubo.model).xyz;
    output_vertex.uv          = input_vertex.uv;    
    
    return output_vertex;
}
  
 
// =========================================================================== //
// FRAGMENT SHADER
// =========================================================================== //
//
// =========================================================================== //
// Structs
// =========================================================================== //

// struct pbr_config
// {
//     float  normal_strength;
//     float  roughness_strength;
//     float4 color_tint;
// };



// =========================================================================== //
// Bindings
// =========================================================================== //


// =========================================================================== //

float3 SimpleLighting(float3 position, float3 normal)
{
	float3 lightPos    = float3(-1, -2, 6);
	float3 L           = lightPos - position;
	float3 N           = normalize(normal);
	float ambientValue = 0.0;
	return float3(dot(L, N));
}


[shader("fragment")]
float4 Fragment_Main(VertexOutput in_vertex) : SV_Target
{ 
    float3 col = SimpleLighting(in_vertex.wc_position, in_vertex.normal) ;    
    return float4(in_vertex.normal, 1);	
}

// =========================================================================== // 