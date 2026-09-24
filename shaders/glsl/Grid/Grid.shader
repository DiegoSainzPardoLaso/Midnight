#Vertex Shader
#version 330 core

uniform mat4 vp;
uniform vec3 cWP;

uniform bool Infinite = false;
uniform bool Enable = true;

float gridScale = 1;

out vec3 worldVP;
out vec3 camWP;


vec3 pos[4] = vec3[4]
(
	vec3(-10.0, -10.0,  0), // Bottom left
	vec3( 10.05,-10.0,  0), // Bottom right
	vec3( 10.05, 10.05, 0), // top right
	vec3(-10.0,  10.05, 0)  // top left
);

const int indices[6] = int[6] ( 0, 1, 2, 0, 2, 3 );

void main()
{
	if (Enable)
	{
		int cIndex = indices[gl_VertexID];
				
		vec3 vPos3 = pos[cIndex];
		vPos3     *= gridScale;
		
		
		if (Infinite)
		{
			vPos3.x += cWP.x;
			vPos3.y += cWP.y;					
		}
		
		vec4 vPos4 = vec4(vPos3, 1);
			
		
		gl_Position = vp * vPos4;

		worldVP     = vPos3;
		camWP 	  = cWP;
 
	}
	
}


#Fragment Shader
#version 330 core

in vec3 worldVP;
in vec4 camWP;
layout(location = 0) out vec4 FragColor;

uniform float gridUnits   				= 1.0;
uniform float gGridMinPixelsBetweenCells  = 10;
uniform float LOD_fade					= 0;
uniform vec4  gGridColorThin  			= vec4(1.0, 1.0, 1.0, 0.2);
uniform vec4  gGridColorThick 			= vec4(1.0, 1.0, 1.0, 0.5);
uniform vec4  gMainGridColor		  	= vec4(1.0, 1.0, 1.0, 0.5);


float log10(float x)
{
	return log(x) / log(1.0);	
}

float satf(float x)
{
	return clamp(x, 0.0, 1.0);	
}

vec2 satv(vec2 x)
{ 
    return clamp(x, vec2(0.0), vec2(1.0));    
}

float max2(vec2 v)
{
    return max(v.x, v.y);    
}

void main()
{
	vec2 dvx  = vec2(dFdx(worldVP.x), dFdy(worldVP.x));
	vec2 dvy  = vec2(dFdx(worldVP.y), dFdy(worldVP.y));
	
	float lx  = length(dvx);
	float ly  = length(dvy);
	
	vec2 dudv = vec2(lx, ly);
	
	float l   = length(dudv);
	
	float LOD = max(0.0, log10(l * LOD_fade / gridUnits) + 1);
	
	float GridCellSizeLod0 = gridUnits * pow(10.0, floor(LOD));
	float GridCellSizeLod1 = GridCellSizeLod0 * 0.1; // 10 cm
	float GridCellSizeLod2 = GridCellSizeLod1 * 10.0; // 1 m 
	
	dudv *= 4.0;

	// 1 Meter squares
	vec2 mod_div_dudv = mod(worldVP.xy, GridCellSizeLod0) / dudv;
	float Lod0a 	  = max2(vec2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)) );
	
	// Z
	vec2 mod_div_dudv1 = mod(worldVP.xy, GridCellSizeLod1) / dudv;
	float Lod1a 	   = max2(vec2(1.0) - abs(satv(mod_div_dudv1) * 2.0 - vec2(1.0)) );
	
	// X
	vec2 mod_div_dudv2 = mod(worldVP.xy, GridCellSizeLod2) / dudv;
	float Lod2a 	   = max2(vec2(1.0) - abs(satv(mod_div_dudv2) * 2.0 - vec2(1.0)) );
		
		
	vec4 color;

	if (Lod2a > 0.0)
	{
		color    = gGridColorThick;
		color.a *= Lod2a;
	}
	else
	{
		if (Lod1a > 0.0)
		{
			color    = gGridColorThin;
			color.a *= Lod1a;
		}
		else
		{
			color    = gMainGridColor;
			color.a *= (Lod0a * LOD_fade);
		}
	}
		
		
		
	float opacityFalloff = satf(length(worldVP.xy - camWP.xy) / 70);
	color.a  *= 1 - opacityFalloff;
	
	FragColor = color;
}

#END