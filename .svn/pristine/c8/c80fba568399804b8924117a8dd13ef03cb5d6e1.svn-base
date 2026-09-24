#Vertex Shader
#version 330 core

layout (location = 0) in vec3 in_vertexPosition;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_uv;

uniform vec2 transform;
uniform vec2 res;

out vec2 UVCoords;
out vec3 vertexColor;

void main()
{	
	vec2 movedPos = in_vertexPosition.xy + transform;   
	vec4 nPosNDC  = vec4(movedPos.x / res.x * 2 - 1,
				    1 - (movedPos.y / res.y * 2), 0.0, 1.0);	

    gl_Position = nPosNDC;
	UVCoords    = in_uv;
    vertexColor = in_color;
}

#Fragment Shader
#version 330 core

in vec3  vertexColor; 
in vec2  UVCoords;

out vec4 outColor; 

vec4 color;
uniform sampler2D fontAtlas;

void main()
{		

    outColor = texture(fontAtlas, UVCoords) * vec4(1, 1, 1, 1.0);
}


#END