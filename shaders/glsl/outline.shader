#Vertex Shader
#version 330 core

layout(location = 0) in vec3 in_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * 2.0 * vec4(in_position, 1.0);
}

#Fragment Shader
#version 330 core

uniform vec4 outline_color;

out vec4 out_color;

void main()
{
    out_color = outline_color;
}


#END