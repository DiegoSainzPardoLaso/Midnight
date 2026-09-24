#Vertex Shader
#version 330 core

layout(location = 0) in vec3 in_v_position;
layout(location = 1) in vec3 in_v_color;
layout(location = 2) in vec3 in_v_normal;
layout(location = 3) in vec2 in_v_uv;

uniform mat4 mvp;

out vec3 v_pos;
out vec3 v_col;
out vec3 v_nor;
out vec2 v_uv;

void main()
{
    vec4 f_position = mvp * vec4(in_v_position, 1.0);    
    gl_Position     = f_position;
    
    v_pos = in_v_position;
    v_col = in_v_color;
    v_nor = in_v_normal;
    v_uv  = in_v_uv;
}

#Fragment Shader
#version 330 core

in vec3 v_pos;
in vec3 v_col;
in vec3 v_nor;
in vec2 v_uv;

out vec4 out_color;

vec3 simple_lighting()
{
	vec3 lightPos      = vec3(-1, -2, 6);
	vec3 L             = lightPos - v_pos;
	vec3 N             = normalize(v_nor);
	float ambientValue = 0.0;
	return vec3(dot(L, N));
}


void main()
{
    vec3 light_color = simple_lighting() * 2.0f;
    out_color = normalize(vec4(light_color, 1.0) + 10.05) * vec4(v_col, 1.0) + (vec4(-v_nor, 1) * 0.25);     
}

#END