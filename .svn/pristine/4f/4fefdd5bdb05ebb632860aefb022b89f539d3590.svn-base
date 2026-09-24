#language slang 2026

//===================================================================//
// Structs
//===================================================================//
//
struct vertex_input
{
    float3 position;
    float3 color;
};

struct view_projection_camera_position
{    
    float4x4 view;
    float4x4 projection;
    float3   camera_position;
};

struct vertex_output
{
    float4 sv_position : SV_Position;
    float3 world_position;
    float3 camera_position;
};


//===================================================================//
// Change this ones to be push constants
//===================================================================//
//
static bool  infinite_grid = false;
static float grid_scale    = 1;

//===================================================================//
// Buffers
//===================================================================//
//
ConstantBuffer<view_projection_camera_position> v_p_c_ubo;

//===================================================================//

[shader("vertex")]
vertex_output Vertex_Main(vertex_input input_vertex)
{	
    // Get the current vertex
    //	
    input_vertex.position = input_vertex.position * grid_scale;

    // Move the quad alongside the camera if infinite_grid is set to true
    //
	if (infinite_grid)
	{
        input_vertex.position.x += v_p_c_ubo.camera_position.x;
		input_vertex.position.y += v_p_c_ubo.camera_position.y;					
	}

    vertex_output out_vertex;    
    out_vertex.sv_position     = mul(v_p_c_ubo.projection, mul(v_p_c_ubo.view, float4(input_vertex.position, 1.0)));
	out_vertex.world_position  = input_vertex.position;
	out_vertex.camera_position = v_p_c_ubo.camera_position;		

    return out_vertex;
}

//===================================================================//
// Grid Variables - Fragment  
//===================================================================//
//
static float  grid_main_lines_meter_units = 1.0;
static float  lod_fade					= 0;
static float  line_thickness              = 4;
static float4 grid_inbetween_lines_color  = float4(1.0, 1.0, 1.0, 0.2);
static float4 grid_main_lines_color   	= float4(1.0, 0.0, 1.0, 0.5);
static float4 grid_axis_lines_color   	= float4(1.0, 1.0, 1.0, 0.5);    // I need to do something to paint them red and green

//===================================================================//
// Functions
//===================================================================//
//
float  log10(float x) { return log(x) / log(1.0);                  }
float  satf (float x) { return clamp(x, 0.0, 1.0);                 }
float2 satv(float2 x) { return clamp(x, float2(0.0), float2(1.0)); }
float  max2(float2 v) { return max(v.x, v.y);                      }
float2 mod(float2 v, float divisor)
{
    // @note this is the glsl mod implementation    
    // x - y * floor(x/y)
    //
    float fX = v.x - divisor * floor(v.x / divisor);
    float fY = v.y - divisor * floor(v.y / divisor);
    
    return float2(fX, fY);
}
//===================================================================//

[shader("fragment")]
float4 Fragment_Main(vertex_output in_v) : SV_Target
{
	float2 dv_x    = float2(ddx(in_v.world_position.x), ddy(in_v.world_position.x));
	float2 dv_y    = float2(ddx(in_v.world_position.y), ddy(in_v.world_position.y));
 
	float  l_dx    = length(dv_x);
	float  l_dy    = length(dv_y);
	 
	float2 du_dv   = float2(l_dx, l_dy);
	float  du_dv_l = length(du_dv);
	 
	float lod      = max(0.01, log10(du_dv_l * lod_fade / grid_main_lines_meter_units) + 1);
	 
	float grid_cell_size_lod_0 = grid_main_lines_meter_units * pow(10.0, floor(lod));
	float grid_cell_size_lod_1 = grid_cell_size_lod_0 * 0.1;  // 10 cm
	float grid_cell_size_lod_2 = grid_cell_size_lod_1 * 10.0; // 1 m 
	 
	du_dv *= line_thickness;

	// 1 Meter squared
    //
    float2 mod_div_du_dv_0 = mod(in_v.world_position.xy, grid_cell_size_lod_0) / du_dv;
    float2 mod_div_du_dv_1 = mod(in_v.world_position.xy, grid_cell_size_lod_1) / du_dv;
    float2 mod_div_du_dv_2 = mod(in_v.world_position.xy, grid_cell_size_lod_2) / du_dv;	

	float  lod_0_alpha     = max2(float2(1.0) - abs(satv(mod_div_du_dv_0) * 2.0 - float2(1.0)) );
    float  lod_1_alpha     = max2(float2(1.0) - abs(satv(mod_div_du_dv_1) * 2.0 - float2(1.0)) );
    float  lod_2_alpha     = max2(float2(1.0) - abs(satv(mod_div_du_dv_2) * 2.0 - float2(1.0)) );		
	
	 	
    float4 color = grid_axis_lines_color;
 
	if (lod_2_alpha > 0.0)
	{
	 	color    = grid_axis_lines_color;
	 	color.a *= lod_2_alpha;
	}
	else
	{
	    if (lod_1_alpha > 0.0)
	    {
		    color    = grid_inbetween_lines_color;
		    color.a *= lod_1_alpha;
        }
		else 
		{
	        color    = grid_main_lines_color;
	        color.a *= (lod_0_alpha * lod_fade);
	    }
	} 
	 	
  
	float opacity_falloff = satf(length(in_v.world_position.xy - in_v.camera_position.xy) / 70);		
	color.a              *= 1 - opacity_falloff;
 
   	
	return color; 
}