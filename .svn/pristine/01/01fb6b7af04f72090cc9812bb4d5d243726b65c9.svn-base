#Vertex Shader
#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 uv;

uniform vec4 color;
uniform vec4 transform;
uniform vec2 resolution;

out vec2 UVCoords;
out vec4 currentColor;

void main()
{
	vec2 cOffset = vPos.xy;
	vec2 nPos;
	nPos.x = 	  cOffset.x / resolution.x * 2 - 1;
	nPos.y = 1 - (cOffset.y / resolution.y * 2);

    gl_Position  = vec4(nPos, 0.0, 1.0);
	UVCoords     = uv;
	currentColor = color;
}


#Fragment Shader
#version 330 core

in vec3  vertexColor; 
in vec2  UVCoords;
in vec4  currentColor;

out vec4 outColor; 

uniform sampler2D albedo;

void main()
{	
    outColor = currentColor;
}


#END