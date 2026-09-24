#Vertex Shader
#version 330 core


layout(location = 0) in vec3 vPos;
layout(location = 0) in vec2 uvCoords;


uniform vec4 transform;
uniform vec2 res;

out vec4 trans;
out vec2 resolution;

void main()
{
	vec2 nPos = vPos.xy;
	nPos.x    = 	 nPos.x / res.x * 2.0 - 1.0;
	nPos.y    = 1 - (nPos.y / res.y * 2.0);
	
	gl_Position = vec4(nPos, 0.0, 1.0);
	resolution  = res;
	trans       = transform;
}

#Fragment Shader
#version 330 core

in vec4 trans;
in vec2 resolution;
 
vec4 fColor = vec4(0.1, 0.1, 0.1, 0.75);

out vec4 color;

void main()
{
	color = fColor;
}

#END