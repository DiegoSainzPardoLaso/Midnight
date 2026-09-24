#language slang 2026

struct vertex_input
{
    float3 position;
    float3 color;
    float3 normal;
    float2 uv;
};

struct model_view_projection_ubo
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

struct vertex_output
{
    float4 sv_position : SV_Position;
    float3 ws_position;
    float3 normal;
};

ConstantBuffer<model_view_projection_ubo> mvp;
[shader("vertex")]
vertex_output Vertex_Main(vertex_input v)
{
    vertex_output out_v;
    out_v.sv_position = mul(mvp.projection, mul(mvp.view, mul(mvp.model, float4(v.position.xyz, 1))));
    out_v.ws_position = v.position;
    out_v.normal      = v.normal;
    
    return out_v;
}

float3 simple_lighting(float3 position, float3 normal)
{
	float3 lightPos      = float3(-10, 0, 5);
	float3 L             = lightPos - position;
	float3 N             = normalize(normal);
	float ambient_value  = 0.8;
	return normalize(float3(dot(L, N))) + ambient_value;
}  

[shader("fragment")]
float4 Fragment_Main(vertex_output vertex)
{    
    float3 light = simple_lighting(vertex.ws_position, vertex.normal);
    return float4(1, 0, 1, 1) * float4(light, 1.0);
}
