#Vertex Shader
#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;

void main()
{	
	gl_Position = projection * view * model * vec4(inPosition, 1.0);
	vertexColor = inColor;    
}


#Fragment Shader
#version 330 core

uniform float in_alpha;
uniform float in_color_multiplier;

// IN
in vec3 vertexColor;

// Out
out vec4 color;

void main()
{
    vec3 new_vertex_color = vec3(vertexColor.x * in_color_multiplier, vertexColor.y * in_color_multiplier, vertexColor.z * in_color_multiplier);
	color = vec4(new_vertex_color, in_alpha);
}

#END
