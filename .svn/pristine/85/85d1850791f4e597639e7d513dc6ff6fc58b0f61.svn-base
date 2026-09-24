#Vertex Shader
#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float in_alpha;

out vec3 vertexColor;
out float alpha;

void main()
{	
	gl_Position = projection * view * model * vec4(inPosition, 1.0);
	vertexColor = inColor;
    alpha       = in_alpha;
}


#Fragment Shader
#version 330 core

// IN
in vec3 vertexColor;
in float alpha;

// Out
out vec4 color;

void main()
{
	color = vec4(vertexColor, alpha);
}

#END
