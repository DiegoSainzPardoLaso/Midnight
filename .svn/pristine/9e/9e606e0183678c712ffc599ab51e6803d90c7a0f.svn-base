#Vertex Shader
#version 330 core

layout(location = 0) in vec3 in_vertex_position;
layout(location = 1) in vec3 in_vertex_color;
layout(location = 2) in vec2 in_vertex_uv;

uniform vec2 resolution;
uniform vec2 transform;

out vec3 vertex_color;
out vec2 vertex_uv;

void main()
{
    // Note: The input positions are alredy defined in NDC space, so transforming them here isn't necessary
    //
    vec4 final_position = vec4(2 * in_vertex_position.x / resolution.x - 1, 
                           1 - 2 * in_vertex_position.y / resolution.y, 0.0f, 1.0f);
                                        
    gl_Position  = final_position;
    vertex_color = in_vertex_color;
    vertex_uv    = in_vertex_uv;
}

#Fragment Shader
#version 330 core

in vec3 vertex_color;
in vec2 vertex_uv;

out vec4 out_color;

void main()
{    
    out_color = vec4(vertex_color, 0.85);
}


#END